
#include <sstream>
#include <map>
#include <fstream>
#include <format>

#include "imnodes.h"

#include "Serialiser.h"
#include "Nodes/Node.h"
#include "Nodes/SourceNode.h"
#include "Nodes/TextNode.h"

bool Serialiser::SerialiseEditorState(
	const std::string& filePath,
	const std::vector<std::shared_ptr<Node>>& nodes,
	const std::vector<std::pair<int, int>>& links,
	std::string& errStr)
{
	/*
		For now the json format is as follows:
		{ // top level object
			"nodes" : [ // nodes array
				{ // single node object
					"text": (str) sanitised node printable content,
					"id": (int) the nodes id,
					"terminating": (bool) does the node terminate the control flow,
					"posx": (float) x position of the node in the editor,
					"posy": (float) y position of the node in the editor.
					"inputs": [ // input pins array
						(int) input pin's id,
						.
						.
						.
					],
					"outputs": [ // output pins array
						{ // single output pin object
							"text": (str) matching text,
							"destination": (int) input pin id connected to this output pin
						},
						.
						.
						.
					]
				}
				.
				.
				.
			]
		}
		The actual json has minimal whitespace excluding spaces and new lines/carriage returns.
		We may then naturally load the nodes vector, and we may construct the links vector from the sum
		of all the nodes outputs arrays, using the destination field
	*/

	// Setup link's map (outputPins to inputPins)
	// Nicer than finding the link every time we need it
	std::map<int, int> linksMap;
	for (const std::pair<int, int>& link : links) {
		linksMap[link.first] = link.second;
	}

	// json stringstream
	std::ostringstream json;

	// Start json
	json << "{\n";

	// Start nodes section
	json << "\"nodes\":[\n";

	// Populate nodes section
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		const std::shared_ptr<Node>& node = *it;
		Serialiser::SerialiseNodeToStream(json, node, linksMap, errStr);
		if (std::next(it) != nodes.end()) {
			json << ",\n";
		}
	}

	// End nodes section
	json << "]\n";

	// End json file
	json << "}";

	// Output to file
	std::ofstream jsonFile(filePath, std::ios::out);
	if (!jsonFile.is_open()) {
		errStr = "Failed to open output file at path: " + filePath;
		return false;
	}
	jsonFile << json.str();

	return true;
}

bool Serialiser::DeserialiseEditorState(
	const std::string& filePath,
	std::vector<std::shared_ptr<Node>>& nodes,
	std::vector<std::pair<int, int>>& links,
	std::string& errStr)
{
	json jsonObject;

	{ // Parse the saved file
		std::ifstream jsonFile(filePath);
		if (!jsonFile.is_open()) {
			errStr = "Failed to open json file at path: " + filePath;
			return false;
		}
		jsonObject = json::parse(jsonFile);
		jsonFile.close();
	}
	{ // Iterate over the nodes object
		// Does the nodes object exist
		if (!jsonObject.contains("nodes")) {
			errStr = "Could not find nodes object in json at path: " + filePath;
			return false;
		}

		// Get nodes object
		auto& nodesObject = jsonObject.at("nodes");
		if (!nodesObject.is_array()) {
			errStr = "Nodes object is not an array in json at path: " + filePath;
			return false;
		}

		// Iterate over its elements
		auto nodeIterator = nodesObject.begin();
		std::shared_ptr<Node> newNode;

		// If the json is well formed the first node will be the source node
		if (!DeserialiseSourceNode(nodeIterator, nodes, links, errStr)) {
			errStr = "Source node deserialisation error: " + errStr + " in json at path: " + filePath;
			return false;
		}

		// Get next node object
		++nodeIterator;

		// Do the rest of the nodes
		while (nodeIterator != nodesObject.end()) {
			// Deserialise this node
			DeserialiseNode(nodeIterator, nodes, links, errStr);

			// Get next node object
			++nodeIterator;
		}
	}

	/*
	// Storage for the text of the json file
	std::string jsonStr;

	{ // Open and read from file
		// Open file and setup for reading
		std::ifstream jsonFile(filePath);
		std::ostringstream jsonStream;
		std::string line;

		// Check for successful file open
		if (!jsonFile.is_open()) {
			errStr = "Failed to open json file at path: " + filePath;
			return false;
		}

		// Read file to string for parsing
		while (std::getline(jsonFile, line)) {
			jsonStream << line << "\n";
		}

		// Close file
		jsonFile.close();

		// Output string
		jsonStr = jsonStream.str();
	}
	{ // Parse json string
		// Iterate over the string
		for (int k = 0; k < jsonStr.size(); ++k) {
			char c = jsonStr[k];
		}

		// Get source node
		std::shared_ptr<Node> sourceNode = std::make_shared<SourceNode>();
		
	}
	*/

	return true;
}

// TODO implement a json string sanitiser
std::string Serialiser::Sanitise(const std::string& str) {
	return str;
}

bool Serialiser::SerialiseNodeToStream(
	std::ostringstream& stream,
	const std::shared_ptr<Node>& node,
	const std::map<int, int>& linksMap,
	std::string& errStr)
{
	// Start node
	stream << "{\n";

	// Basic node information
	stream << "\"text\": \"" << Serialiser::Sanitise(node->GetPrintableContent()) << "\",\n"
		   << "\"id\": " << node->GetID() << ",\n"
		   << "\"terminating\": " << node->IsTerminating() << ",\n";

	// Position information
	ImVec2 pos = ImNodes::GetNodeEditorSpacePos(node->GetID());
	stream << "\"posx\": " << pos.x << ",\n"
		   << "\"posy\": " << pos.y << ",\n";

	// Input pins
	stream << "\"inputs\": [";
	for (auto it = node->GetInputPins().begin(); it != node->GetInputPins().end(); ++it) {
		const std::shared_ptr<InputPin>& inPin = *it;
		stream << inPin->GetID();
		// If not the last pin
		if (std::next(it) != node->GetInputPins().end()) {
			stream << ", ";
		}
	}
	stream << "]";

	// Only do output pins if non-terminating
	if (!node->IsTerminating()) {
		stream << ",\n";
		// Output pins
		stream << "\"outputs\": [\n";
		for (auto it = node->GetOutputPins().begin(); it != node->GetOutputPins().end(); ++it) {
			const std::shared_ptr<OutputPin>& outPin = *it;
			// Check if this output pin is linked
			if (linksMap.find(outPin->GetID()) == linksMap.end()) {
				std::ostringstream msg;
				msg << "Non terminating node with unlinked output pin. NodeID: " << node->GetID() << "pinID: " << outPin->GetID();
				errStr += msg.str();
			}

			// Record the output pin
			stream << "{"
				   << "\"text\": \"" << outPin->GetMatchString() << "\", "
				   << "\"destination\": " << linksMap.at(outPin->GetID())
				   << "}";

			// If not the last pin
			if (std::next(it) != node->GetOutputPins().end()) {
				stream << ",";
			}
			stream << "\n";
		}
		stream << "]";
	}

	// End node
	stream << "\n}";

	return true;
}

bool Serialiser::DeserialiseSourceNode(
	json::iterator nodeIterator,
	std::vector<std::shared_ptr<Node>>& nodes,
	std::vector<std::pair<int, int>>& links,
	std::string& errStr)
{
	// Make node
	std::shared_ptr<Node> newNode = std::make_shared<SourceNode>();

	// Get the output pin
	if (nodeIterator->contains("outputs")) {
		errStr = "Source node doesn't contain outputs field, json poorly formed.";
		return false;
	}
	for (auto& outPin : nodeIterator->at("outputs")) { // There should be only one
		int id = newNode->AddOutputPin();
		links.emplace_back(id, outPin.at("destination"));
	}
	nodes.push_back(newNode);

	return true;
}

bool Serialiser::DeserialiseNode(
	const json::iterator& nodeIterator,
	std::vector<std::shared_ptr<Node>>& nodes,
	std::vector<std::pair<int, int>>& links,
	std::string& errStr)
{
	// Object to extract json data to
	JsonNode deserialisedNode;

	// Deserialise json to JsonNode
	if (!ValidateAndFetchNode(nodeIterator, deserialisedNode, errStr)) {
		errStr = "Failed to fetch and validate node during deserialisation. " + errStr;
		return false;
	}

	// Make actual node
	std::shared_ptr<Node> newNode = std::make_shared<TextNode>(deserialisedNode.id, deserialisedNode.text);

	// Add input pins
	for (auto& inPin : deserialisedNode.inputs) {
		newNode->AddInputPin(inPin);
	}

	// Set terminating flag
	newNode->SetTerminating(deserialisedNode.terminating);

	// If non terminating
	if (!deserialisedNode.terminating) {
		// Add output pins
		for (auto& outPin : deserialisedNode.outputs) {
			int id = newNode->AddOutputTextPin(outPin.matchText);
			// Add link from this output
			links.emplace_back(id, outPin.destination);
		}
	}

	// Set node location
	ImNodes::SetNodeEditorSpacePos(deserialisedNode.id, ImVec2(deserialisedNode.posx, deserialisedNode.posy));

	// Add to node vector
	nodes.push_back(newNode);

	return true;
}

bool Serialiser::ValidateAndFetchNode(
	const json::iterator& nodeIterator,
	JsonNode& newNode,
	std::string& errStr)
{
	// Check for validity and assign

	// Id
	if (!nodeIterator->contains("id")) {
		errStr = "Node doesn't contain id field, json poorly formed.";
		return false;
	}
	newNode.id = nodeIterator->at("id");

	// Text
	if (!nodeIterator->contains("text")) {
		errStr = "Node doesn't contain text field, json poorly formed.";
		return false;
	}
	newNode.text = nodeIterator->at("text");

	// Terminating flag
	if (!nodeIterator->contains("terminating")) {
		errStr = "Node doesn't contain terminating field, json poorly formed.";
		return false;
	}
	newNode.terminating = nodeIterator->at("terminating");

	// Positions
	if (!nodeIterator->contains("posx")) {
		errStr = "Node doesn't contain posx field, json poorly formed.";
		return false;
	}
	newNode.posx = nodeIterator->at("posx");

	if (!nodeIterator->contains("posy")) {
		errStr = "Node doesn't contain posy field, json poorly formed.";
		return false;
	}
	newNode.posy = nodeIterator->at("posy");

	// Inputs
	if (!nodeIterator->contains("inputs")) {
		errStr = "Node doesn't contain inputs field, json poorly formed.";
		return false;
	}
	for (auto& inPin : nodeIterator->at("inputs")) {
		newNode.inputs.push_back(inPin);
	}

	// Outputs
	if (!newNode.terminating) {
		if (!nodeIterator->contains("outputs")) {
			errStr = "Non terminating node doesn't contain outputs field, json poorly formed.";
			return false;
		}
		for (auto& outPin : nodeIterator->at("outputs")) {
			if (!outPin.contains("text")) {
				errStr = "Outputs malformed, text field missing, json poorly formed.";
				return false;
			}
			if (!outPin.contains("destination")) {
				errStr = "Outputs malformed, destination field missing, json poorly formed.";
				return false;
			}
			newNode.outputs.push_back({ outPin.at("text"), outPin.at("destination") });
		}
	}

	return true;
}
