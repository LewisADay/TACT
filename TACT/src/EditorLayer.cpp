
#include <iostream>
#include <memory>

#include "imgui.h"
#include "imnodes.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h" // SeparatorEx

#include "EditorLayer.h"
#include "Nodes/TextNode.h"
#include "Nodes/SourceNode.h"
#include "TextAdventureGame.h"


void EditorLayer::OnAttach() {
	ImNodes::CreateContext();

	// Create the source node
	std::shared_ptr<SourceNode> m_SourceNode = std::make_shared<SourceNode>();
	m_Nodes.push_back(m_SourceNode);
}

void EditorLayer::OnDetach() {
	ImNodes::DestroyContext();
}

void EditorLayer::OnUIRender() {
	RenderSidewindow();
	RenderMainwindow();
	LinkOperations();
	SelectedNodeManagement();
}

// TODO
void EditorLayer::Save(){}

// TODO
void EditorLayer::Load(){}

void EditorLayer::BuildGame() {
	TextAdventureGame game(m_Nodes, m_Links);
	std::string errStr;
	if (!game.Build(errStr)) {
		// TODO
		// Log error string - probably add logging in general too
		std::cerr << "Error building game!\n" + errStr << std::endl;
		// Report to the user
	}
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

	RightClickMenu();

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

void EditorLayer::LinkOperations() {
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

void EditorLayer::SelectedNodeManagement() {
	int nodeID;
	if (ImNodes::IsNodeHovered(&nodeID) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		for (int k = 0; k < m_Nodes.size(); ++k) {
			if (m_Nodes[k]->GetID() == nodeID) {
				m_ActiveNode = m_Nodes[k]; // Shared ptr ref++
			}
		}
	}
}

void EditorLayer::RightClickMenu() {
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)
        && ImNodes::IsEditorHovered()
		&& ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		ImGui::OpenPopup("##RightClickMenu");
	}

	if (ImGui::BeginPopup("##RightClickMenu")) {
		// Maybe make an enum so we can call a Add(enum) method
		// which then calls the appropriate AddXXX method, e.g. AddTextNode()
		int selection = -1;
		std::vector<char*> options = { "Text Node" };
		ImGui::Text("---- Add Node ----");
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
		for (int k = 0; k < options.size(); ++k) {
			if (ImGui::Selectable(options[k])) { selection = k; }
		}
		ImGui::EndPopup();

		// Early return if we haven't selected anything
		if (selection == -1) { return; }

		NewNode(static_cast<NodeType>(selection));
	}
}

int EditorLayer::GetNextNodeID() { return ++_NodeID; }

void EditorLayer::NewNode(NodeType type) {
	switch (type)
	{
	case EditorLayer::Text:
		NewTextNode();
		break;
	default: // Default should probably throw or otherwise log TODO
		break;
	}
}

void EditorLayer::NewTextNode() {
	int id = GetNextNodeID();
	std::shared_ptr<TextNode> textNode = std::make_shared<TextNode>(id);
	textNode->AddInputPin();
	textNode->AddOutputPin();
	
	ImNodes::SetNodeScreenSpacePos(id, ImGui::GetMousePos());

	m_Nodes.push_back(textNode);
}
