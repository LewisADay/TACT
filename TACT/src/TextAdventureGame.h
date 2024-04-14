#pragma once

#include <vector>
#include <memory>

#include "Nodes/Node.h"

class TextAdventureGame {

public: // Public methods

	/// <summary>
	/// Construct a new text adventure game from these nodes and links
	/// </summary>
	/// <param name="nodes"></param>
	/// <param name="links"></param>
	TextAdventureGame(const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::pair<int, int>>& links);

	/// <summary>
	/// Build the game
	/// </summary>
	/// <param name="errStr">Error message, if an error occured</param>
	/// <returns>If the build completed successfully</returns>
	bool Build(std::string& errStr);

private:
	const std::vector<std::shared_ptr<Node>>& m_Nodes;
	const std::vector<std::pair<int, int>>& m_Links;
};
