
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
	m_SourceNode = std::make_shared<SourceNode>();
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
void EditorLayer::Save() {
	// Serialise the m_Nodes and m_Links vectors
	// Will probably need to use reflection to get the node types
	// so they can be serialised
	// Record the m_Nodes ID's and those ID's positions
}

// TODO
void EditorLayer::Load() {}

void EditorLayer::GenerateGame() {
	TextAdventureGame game(m_SourceNode, m_Nodes, m_Links);
	std::string errStr;
	if (!game.Generate(errStr)) {
		// Report to the user
		m_GenerationErr = true;
		m_GenerationErrStr = errStr;
	}
}

void EditorLayer::RenderSidewindow() {
	ImGui::Begin("Properties");

	if (m_GenerationErr) {
		m_ActiveNode = nullptr;
	}

	if (ImGui::Button("Help")) {
		m_ActiveNode = nullptr;
		m_GenerationErr = false;
	}

	if (m_ActiveNode) { m_ActiveNode->RenderProperties(); }
	else if (m_GenerationErr) {
		ImGui::TextWrapped("Generation Error!");
		ImGui::TextWrapped(m_GenerationErrStr.c_str());
	}
	else {
		ImGui::Bullet(); ImGui::TextWrapped("Left click-and-drag on a node to move it.");
		ImGui::Bullet(); ImGui::TextWrapped("Left click on a node to display it's properties in this panel.");
		ImGui::Bullet(); ImGui::TextWrapped("Middle mouse click-and-drag on the canvas to move the viewport.");
		ImGui::Bullet(); ImGui::TextWrapped("Right click on the canvas to open the add new node menu.");
	}
	
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

// 
void EditorLayer::RightClickMenu() {

	// See if we wish to open the right click menu
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)
        && ImNodes::IsEditorHovered()
		&& ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		ImGui::OpenPopup("##RightClickMenu");
	}

	// If we want to open the menu, this is it's description
	if (ImGui::BeginPopup("##RightClickMenu")) {

		// The selected node to add
		int selection = -1;

		// Vector of available options (currently only TextNodes are implemented)
		std::vector<char*> options = { "Text Node" };

		// TODO: Styling, borders etc. (It looks quite squashed)
		// Menu title and horizontal separator
		ImGui::Text("---- Add Node ----");
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);

		// Display options as selectables and record what is selected
		for (int k = 0; k < options.size(); ++k) {
			if (ImGui::Selectable(options[k])) { selection = k; }
		}

		// End of popup description
		ImGui::EndPopup();

		// Early return if we haven't selected anything
		if (selection == -1) { return; }

		// Make new node
		NewNode(static_cast<NodeType>(selection));
	}
}

int EditorLayer::GetNextNodeID() { return ++_NodeID; }

void EditorLayer::NewNode(const NodeType& type) {
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
