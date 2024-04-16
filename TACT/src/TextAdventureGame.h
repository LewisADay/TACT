#pragma once

#include <vector>
#include <memory>
#include <sstream>

#include "Nodes/Node.h"
#include "Nodes/SourceNode.h"

/// <summary>
/// For generating Text Adventure Games from the editor information
/// </summary>
class TextAdventureGame {
public: // Public methods

	/// <summary>
	/// Construct a new text adventure game
	/// </summary>
	/// <param name="source">Source node to use as TAG entrypoint</param>
	/// <param name="nodes">Editor nodes used to construct the game</param>
	/// <param name="links">Editor links used to construct the game</param>
	TextAdventureGame( // We don't want to own any of these so we keep them as const references to prevent copies etc.
		const std::shared_ptr<SourceNode>& source,
		const std::vector<std::shared_ptr<Node>>& nodes,
		const std::vector<std::pair<int, int>>& links);

	/// <summary>
	/// Generate the game files
	/// </summary>
	/// <param name="errStr">Contains the error message, if an error occured</param>
	/// <returns>If the game generated successfully</returns>
	bool Generate(std::string& errStr);

private: // Private enums and classes
	enum TAGErr {
		InvalidGraph,
		UnlinkedSource,
		ReachedNonTerminatingWithoutOutput
	};

private: // Private methods

	// Relics of an older idea - left for future use when we abandon batch
	std::vector<std::shared_ptr<Node>> GetDownstreamNodes(const std::shared_ptr<Node>& usNode);
	bool HasInputPin(const std::shared_ptr<Node>& node, const int& id);

	// TODO Abandon batch
	bool ProcessNode(const std::shared_ptr<Node>& node, std::string& errStr);

	// TODO Rename
	std::string& GetErrorStr(TAGErr err, std::string& str);

	//void AddUserChoiceSection
private: // Private members
	const std::shared_ptr<SourceNode>& m_SourceNode;
	const std::vector<std::shared_ptr<Node>>& m_Nodes;
	const std::vector<std::pair<int, int>>& m_Links;
	const std::string m_OutputFilePath = "../TAG.bat"; // TODO: Use something other than batch as an output
	std::ostringstream m_OutputStream;
};
