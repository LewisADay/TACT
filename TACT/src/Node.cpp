
#include "imgui.h"
#include "imnodes.h"

#include "Node.h"

Node::Node(int id) :
	m_ID(id) {}

void Node::Render() {
	ImNodes::BeginNode(m_ID);

	ImGui::Dummy(ImVec2(80.0f, 45.0f));

	ImNodes::EndNode();
}

int Node::GetID() { return m_ID; }
