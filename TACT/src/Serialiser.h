
#include <string>
#include <vector>
#include <map>

#include "nlohmann/json.hpp"

#include "Nodes/Node.h"

#pragma once

class Serialiser {
	using json = nlohmann::json;

public: // Public enums and classes
	struct JsonNode {
		struct JsonOutputPin {
			std::string matchText;
			int destination;
		};

		int id = 0;
		bool terminating = false;
		float posx = 0.0f;
		float posy = 0.0f;
		std::string text;
		std::vector<int> inputs;
		std::vector<JsonOutputPin> outputs;
	};
	

public: // Public methods

	/// <summary>
	/// Serialise the editor state described by the nodes and links vectors provided to a json file.
	/// </summary>
	/// <param name="filePath">json file to serialise to</param>
	/// <param name="nodes">The nodes active in the editor</param>
	/// <param name="links">The links active in the editor</param>
	/// <param name="errStr">Output string if an error occurs during serialisation</param>
	/// <returns>Return true if there was an error in the serialisation</returns>
	static bool SerialiseEditorState(
		const std::string& filePath,
		const std::vector<std::shared_ptr<Node>>& nodes,
		const std::vector<std::pair<int, int>>& links,
		std::string& errStr);

	/// <summary>
	/// Deserialise the data describing an editor state found at the provided path, into the provided vectors.
	/// </summary>
	/// <param name="filePath">json file to deserialise from</param>
	/// <param name="nodes">The nodes active in the editor</param>
	/// <param name="links">The links active in the editor</param>
	/// <param name="errStr">Output string if an error occurs during serialisation</param>
	/// <returns>Return true if there was an error in the serialisation</returns>
	static bool DeserialiseEditorState(
		const std::string& filePath,
		std::vector<std::shared_ptr<Node>>& nodes,
		std::vector<std::pair<int, int>>& links,
		std::string& errStr);

	/// <summary>
	/// Sanitise the given string for json use
	/// </summary>
	/// <param name="str">String to be sanitised</param>
	/// <returns>Sanitised copy of the string</returns>
	static std::string Sanitise(const std::string& str);

private: // Private methods
	static bool SerialiseNodeToStream(
		std::ostringstream& stream,
		const std::shared_ptr<Node>& node,
		const std::map<int, int>& linksMap,
		std::string& errStr);

	// With the iterator pointing at a json object representing the source node
	// deserialise it to the nodes and links vectors provided
	static bool DeserialiseSourceNode(
		json::iterator nodeIterator,
		std::vector<std::shared_ptr<Node>>& nodes,
		std::vector<std::pair<int, int>>& links,
		std::string& errStr);

	static bool DeserialiseNode(
		const json::iterator& nodeIterator,
		std::vector<std::shared_ptr<Node>>& nodes,
		std::vector<std::pair<int, int>>& links,
		std::string& errStr);

	static bool ValidateAndFetchNode(
		const json::iterator& nodeIterator,
		JsonNode& newNode,
		std::string& errStr);
};
