
#include "TextAdventureGame.h"

TextAdventureGame::TextAdventureGame(
	const std::shared_ptr<SourceNode>& source,
	const std::vector<std::shared_ptr<Node>>& nodes,
	const std::vector<std::pair<int, int>>& links)
	:
	m_Nodes(nodes),
	m_Links(links) {}

bool TextAdventureGame::Generate(std::string& errStr) {


	return true;
}
