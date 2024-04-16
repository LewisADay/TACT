
/*
	Don't look in here, it's horrible.
	This is what we call minimum viable product mess
	Currently we output to batch because that means no
	complicated build system for the generated game.
	But it's generally a mess down there, lots of
	assumptions and nastiness.
*/

#include <iostream>
#include <fstream>

#include "TextAdventureGame.h"

TextAdventureGame::TextAdventureGame(
	const std::shared_ptr<SourceNode>& source,
	const std::vector<std::shared_ptr<Node>>& nodes,
	const std::vector<std::pair<int, int>>& links)
	:
	m_SourceNode(source),
	m_Nodes(nodes),
	m_Links(links),
	m_OutputStream("", std::ios_base::app) {}

bool TextAdventureGame::Generate(std::string& errStr) {

	// Copy original state of errStr
	std::string originalStr = errStr;

	// Clear err str
	errStr = "";

	// Start things off
	m_OutputStream.clear();
	m_OutputStream << "@echo off\n" << "title Text Adventure Game\n\n" << ":start\n";

	// Get source node and start tracing the paths
	int sourcePinID = m_SourceNode->GetOutputPins()[0]->GetID();

	// Find the first true node
	auto it = std::find_if(m_Links.begin(), m_Links.end(),
		[&sourcePinID](std::pair<int, int> link) {
			return link.first == sourcePinID;
		}
	);

	// If there is no link from the source node the graph is invalid
	if (it == m_Links.end()) {
		GetErrorStr(InvalidGraph, errStr);
		GetErrorStr(UnlinkedSource, errStr);
		return false;
	}

	// Goto that pin
	m_OutputStream << "goto PIN" << it->second << "\n";

	// Process each node
	for (std::shared_ptr<Node> node : m_Nodes) {
		if (!ProcessNode(node, errStr)) {
			// Node process err, errStr should already be updated
			return false;
		}
	}

	std::ofstream tagDotBat("TAG.bat", std::ios::out);
	if (!tagDotBat.is_open()) { return false; } // Failed to open file

	tagDotBat << m_OutputStream.str();

	tagDotBat.close();

	// Restore original state of errStr if we've got this far
	// That is, we haven't errored out
	errStr = originalStr;

	return true;
}

std::string& TextAdventureGame::GetErrorStr(TAGErr err, std::string& str) {
	switch (err) {
	case TextAdventureGame::InvalidGraph:
		str += "Invalid Graph!";
		break;
	case TextAdventureGame::UnlinkedSource:
		str += "Unlinked Source!";
		break;
	case TextAdventureGame::ReachedNonTerminatingWithoutOutput:
		str += "Reached non-terminating node without an output!";
		break;
	default:
		break;
	}
	return str;
}

std::vector<std::shared_ptr<Node>> TextAdventureGame::GetDownstreamNodes(const std::shared_ptr<Node>& usNode) {

	// Iterate over the upstream node's output pins
	// Seek all links originating from those pins
	const std::vector<std::shared_ptr<OutputPin>>& outputPins = usNode->GetOutputPins();
	std::vector<int> dsPins;
	dsPins.reserve(outputPins.size());
	for (int k = 0; k < outputPins.size(); ++k) {
		// Iterate over the links
		for (int i = 0; i < m_Links.size(); ++i) {
			const std::pair<int, int>& link = m_Links[k];
			if (link.first == usNode->GetID()) {
				dsPins.push_back(link.second);
				// Early out as each output pin supports at most one link
				break;
			}
		}
	}

	// Tthe unsorted downstream nodes
	std::vector<std::shared_ptr<Node>> unsortedDownstreamNodes;
	// Should be exactly the same size as the number of downstream pins
	unsortedDownstreamNodes.reserve(dsPins.size());

	// The indices of the outgoing pins which correspond to the downstream nodes
	std::vector<int> indices;
	// Should be exactly the same size as the number of downstream pins
	indices.reserve(dsPins.size());

	// Iterate over all nodes
	for (int j = 0; j < m_Nodes.size(); ++j) {
		const std::shared_ptr<Node>& node = m_Nodes[j];
		// Iterate over the downstream pin ids
		for (int n = 0; n < dsPins.size(); ++n) {
			if (HasInputPin(node, dsPins[n])) {
				unsortedDownstreamNodes.push_back(node);
				indices.push_back(n);
			}
		}
	}

	// Sort the downstream nodes so they are in output pin order
	std::vector<std::shared_ptr<Node>> downstreamNodes;
	downstreamNodes.reserve(unsortedDownstreamNodes.size());
	for (auto& index : indices) {
		downstreamNodes.push_back(unsortedDownstreamNodes[index]);
	}
	
	return downstreamNodes;
}

bool TextAdventureGame::HasInputPin(const std::shared_ptr<Node>& node, const int& id) {
	for (auto& pin : node->GetInputPins()) {
		if (pin->GetID() == id) { return true; }
	}
	return false;
}

bool TextAdventureGame::ProcessNode(const std::shared_ptr<Node>& node, std::string& errStr) {

	// Make node label
	m_OutputStream << ":NODE" << node->GetID() << "\n";

	// Make input pin labels
	for (auto& inPin : node->GetInputPins()) {
		m_OutputStream << ":PIN" << inPin->GetID() << "\n";
	}

	// Clear the console and print this node's content and prompt
	m_OutputStream
		<< "cls\n"
		<< "echo " << node->GetPrintableContent() << "\n";

	// Early out if terminating node
	if (node->IsTerminating()) {
		m_OutputStream
			<< "echo The End!\n"
			<< "pause\n"
			<< "goto start\n";
		return;
	}

	// Start user choice section
	m_OutputStream << "echo What would you like to do?\n";

	// Get handle for the output pins
	const std::vector<std::shared_ptr<OutputPin>>& oPins = node->GetOutputPins();

	// Check for existence of some output pins
	if (oPins.size() == 0) {
		GetErrorStr(InvalidGraph, errStr);
		GetErrorStr(ReachedNonTerminatingWithoutOutput, errStr);
		return false;
	}

	// Print player options
	for (auto& outPin : oPins) {
		// Skip invalid pins
		if (outPin->GetPinType() == OutputPin::InvalidInput) { continue; }

		m_OutputStream << "echo " << outPin->GetMatchString() << "\n";
	}

	m_OutputStream << "set /p choice=Make your choice:\n";

	// Handle user choice
	// Get iterator for non-invalid input pins
	auto invalidInputCheck = [](std::shared_ptr<OutputPin> pin) {
		return pin->GetPinType() != OutputPin::InvalidInput;
		};
	auto it = std::find_if(oPins.begin(), oPins.end(), invalidInputCheck);

	while (it != oPins.end()) {
		const std::shared_ptr<OutputPin>& outPin = *it;

		// Skip if the invalid input pin
		if (outPin->GetPinType() == OutputPin::InvalidInput) { continue; }

		// Find id of linked pin
		int linkID = std::find_if(m_Links.begin(), m_Links.end(),
			[outPin](const std::pair<int, int> link) {
				return link.first == outPin->GetID();
			})->second;
		// Print set option
		m_OutputStream
			<< "if \"%choice%\"==\"" << outPin->GetMatchString() << "\" (\n"
			<< "\tgoto PIN" << linkID << "\n"
			<< ")\n";

		// Advance the iterator
		it = std::find_if(++it, oPins.end(), invalidInputCheck);
	}

	// Handle an invalid choice
	m_OutputStream
		<< "echo Invalid choice, please choose again\n"
		<< "pause\n"
		<< "goto NODE" << node->GetID() << "\n\n\n";
}
