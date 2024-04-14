
#include "TextAdventureGame.h"

TextAdventureGame::TextAdventureGame(
	const std::shared_ptr<SourceNode>& source,
	const std::vector<std::shared_ptr<Node>>& nodes,
	const std::vector<std::pair<int, int>>& links)
	:
	m_SourceNode(source),
	m_Nodes(nodes),
	m_Links(links) {}

bool TextAdventureGame::Generate(std::string& errStr) {

	// Get source node and start tracing the paths
	int sourceID = m_SourceNode->GetID();
	auto firstLink = std::find_if(
		m_Links.begin(),
		m_Links.end(),
		[sourceID](const std::pair<int, int>& link) {
			return link.first == sourceID;
		});

	// do something with that

	return true;
}

// TODO: Search pin's instead/figure out what we actually want to do
// when it comes to constructing the game and then maybe have another look
std::vector<std::shared_ptr<Node>> TextAdventureGame::GetDownstreamNodes(const int& id) {

	// It occurs to me that I've searched as if m_Links is a vector of
	// pairs of Node IDs, when it's a vector of pairs of Pin IDs.

	// Vector to store the result
	std::vector<std::shared_ptr<Node>> downstreamNodes;

	
	// Iterate over the links
	for (int k = 0; k < m_Links.size(); ++k) {
		const std::pair<int, int>& link = m_Links[k];

		// When we find a link that matches the root node
		if (link.first == id) {

			// Find the other side of the link
			for (int i = 0; i < m_Nodes.size(); ++i) {
				const std::shared_ptr<Node>& node = m_Nodes[i];
				if (node->GetID() == link.second) {
					downstreamNodes.push_back(node);
					break;
				}
			}
		}
	}
	
	return downstreamNodes;
}


