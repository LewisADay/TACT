#pragma once

#include <vector>
#include <memory>

#include "Nodes/Node.h"
#include "Nodes/SourceNode.h"

class TextAdventureGame {

public: // Public methods

	/// <summary>
	/// Construct a new text adventure game from these nodes and links
	/// </summary>
	/// <param name="nodes"></param>
	/// <param name="links"></param>
	TextAdventureGame(
		const std::shared_ptr<SourceNode>& source,
		const std::vector<std::shared_ptr<Node>>& nodes,
		const std::vector<std::pair<int, int>>& links);

	/// <summary>
	/// Generate the game files
	/// </summary>
	/// <param name="errStr">Error message, if an error occured</param>
	/// <returns>If the game generated successfully</returns>
	bool Generate(std::string& errStr);

private:
	const std::shared_ptr<SourceNode>& m_SourceNode;
	const std::vector<std::shared_ptr<Node>>& m_Nodes;
	const std::vector<std::pair<int, int>>& m_Links;
};
