
#include "TextAdventureGame.h"

TextAdventureGame::TextAdventureGame(const std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::pair<int, int>>& links) :
	m_Nodes(nodes),
	m_Links(links) {}

bool TextAdventureGame::Build(std::string& errStr) {
	return true;
}
