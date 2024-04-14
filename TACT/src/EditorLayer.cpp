
#include <iostream>
#include <memory>

#include "imgui.h"
#include "imnodes.h"
#include "misc/cpp/imgui_stdlib.h"

#include "EditorLayer.h"
#include "Nodes/TextNode.h"


void EditorLayer::OnAttach() {
	ImNodes::CreateContext();
}

void EditorLayer::OnDetach() {
	ImNodes::DestroyContext();
}

void EditorLayer::OnUIRender() {
	RenderSidewindow();
	RenderMainwindow();
	CheckLinks();
	CheckForNewSelectedNode();
}

void EditorLayer::RenderSidewindow() {
	ImGui::Begin("Hello There");

	if (m_ActiveNode) { m_ActiveNode->RenderProperties(); }
	else { ImGui::Text("Select a node to customize it."); }
	
	ImGui::End();
}

void EditorLayer::RenderMainwindow() {
	ImGui::Begin("Editor");
	ImNodes::BeginNodeEditor();

	// TODO
	// Can probably make this const reference - but need to check the const-ness
	// of Render, it should be, in which case that can be refactored at a later date
	// Render the nodes
	for (auto& node : m_Nodes) {
		node->Render();
	}

	// Render the links (using index as ID for ImNodes)
	for (int i = 0; i < m_Links.size(); ++i) {
		const std::pair<int, int> link = m_Links[i];
		ImNodes::Link(i, link.first, link.second);
	}

	ImNodes::EndNodeEditor();
	ImGui::End();
}

void EditorLayer::CheckLinks() {
	// Check for new links
	{
		int start_attr, end_attr;
		if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
			m_Links.push_back(std::make_pair(start_attr, end_attr));
		}
	}

	// Check for deleted links
	{
		// Due to how we submit links, the id is NECCESSARILLY it's index in the links vector
		int id;
		if (ImNodes::IsLinkDestroyed(&id)) {
			m_Links.erase(std::next(m_Links.begin(), id));
		}
	}
}

void EditorLayer::CheckForNewSelectedNode() {
	int nodeID;
	if (ImNodes::IsNodeHovered(&nodeID) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		for (int k = 0; k < m_Nodes.size(); ++k) {
			if (m_Nodes[k]->GetID() == nodeID) {
				m_ActiveNode = m_Nodes[k]; // Shared ptr ref++
			}
		}
	}
}

int EditorLayer::GetNextNodeID() { return ++_NodeID; }

void EditorLayer::NewTextNode() {
	std::shared_ptr<TextNode> textNode = std::make_shared<TextNode>(GetNextNodeID());
	textNode->AddInputPin();
	textNode->AddOutputPin();

	m_Nodes.push_back(textNode);
}
