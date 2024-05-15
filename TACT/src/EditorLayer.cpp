
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
#include "Serialiser.h"


void EditorLayer::OnAttach() {
	ImNodes::CreateContext();

	// Create the source node
	m_SourceNode = std::make_shared<SourceNode>();
	m_Nodes.push_back(m_SourceNode);

	// Set initial render pass flag
	m_InitialRenderPass = true;
}

void EditorLayer::OnDetach() {
	ImNodes::DestroyContext();
}

void EditorLayer::OnUIRender() {
	RenderSidewindow();
	RenderMainwindow();
	LinkOperations();
	NodeOperations();
}

void EditorLayer::Save() {
	std::string path = "test.json";
	std::string errStr;
	if (!Serialiser::SerialiseEditorState(path, m_Nodes, m_Links, errStr)) {
		ReportError(errStr);
	}
}

void EditorLayer::Load() {
	m_Nodes.clear();
	m_Links.clear();

	std::string path = "test.json";
	std::string errStr;
	if (!Serialiser::DeserialiseEditorState(path, m_Nodes, m_Links, errStr)) {
		ReportError(errStr);
	}
}

void EditorLayer::GenerateGame() {
	TextAdventureGame game(m_SourceNode, m_Nodes, m_Links);
	std::string errStr;
	if (!game.Generate(errStr)) {
		ReportError(errStr);
	}
}

void EditorLayer::RenderSidewindow() {
	ImGui::Begin("Properties");

	if (ImGui::Button("Help")) {
		m_ActiveNode = nullptr;
		m_ErrFlag = false;
	}

	if (m_ErrFlag && m_ActiveNode == nullptr) {
		ImGui::TextWrapped("Generation Error!");
		ImGui::TextWrapped(m_ErrStr.c_str());
		ImGui::End();
		return;
	}

	if (m_ActiveNode) { m_ActiveNode->RenderProperties(); }
	else {
		ImGui::Bullet(); ImGui::TextWrapped("Left click-and-drag on a node to move it.");
		ImGui::Bullet(); ImGui::TextWrapped("Left click on a node to display it's properties in this panel.");
		ImGui::Bullet(); ImGui::TextWrapped("Middle mouse click-and-drag on the canvas to move the viewport.");
		ImGui::Bullet(); ImGui::TextWrapped("Right click on the canvas to open the add new node menu.");
		ImGui::Bullet(); ImGui::TextWrapped("Delete a node or link by selecting it and pressing DELETE.");
		ImGui::Bullet(); ImGui::TextWrapped("Attach the source node to a text node to get started.");
		ImGui::Bullet(); ImGui::TextWrapped("Each text node that ends the program should be marked as terminating in it's properties.");
	}

	ImGui::End();
}

void EditorLayer::RenderMainwindow() {
	ImGui::Begin("Editor");
	ImNodes::BeginNodeEditor();

	// Initial source node placement
	if (m_InitialRenderPass) {
		ImVec2 size = ImGui::GetWindowSize();
		ImNodes::EditorContextResetPanning(ImVec2(5, size.y / 2));
		m_InitialRenderPass = false;
	}

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

	// Render the minimap must be done just before EndNodeEditor
	if (m_Nodes.size() > 1) {
		ImNodes::MiniMap();
	}

	ImNodes::EndNodeEditor();
	ImGui::End();
}

void EditorLayer::LinkOperations() {

	// Check for new links
	{
		int start_attr, end_attr;
		if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
			// Check to see if this pin already has a link
			for (std::pair<int, int>& link : m_Links) {
				if (link.first == start_attr) { return; }
			}
			// If not, add the link
			m_Links.push_back(std::make_pair(start_attr, end_attr));
		}
	}

	// Check for deleted links
	{
		// Brute force it since the recommended solution below doesn't seem to trigger
		for (int k = 0; k < m_Links.size(); ++k) {
			if (ImNodes::IsLinkSelected(k) && ImGui::IsKeyDown(ImGuiKey_Delete)) {
				m_Links.erase(std::next(m_Links.begin(), k));
				ImNodes::ClearLinkSelection();
			}
		}
		// Due to how we submit links, the id is NECCESSARILLY it's index in the links vector
		/*
		int id;
		if (ImNodes::IsLinkDestroyed(&id)) {
			m_Links.erase(std::next(m_Links.begin(), id));
		}
		*/
	}
}

void EditorLayer::NodeOperations() {

	{ // Node selection for properties
		int nodeID;
		if (ImNodes::IsNodeHovered(&nodeID) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
			for (int k = 0; k < m_Nodes.size(); ++k) {
				if (m_Nodes[k]->GetID() == nodeID) {
					m_ActiveNode = m_Nodes[k]; // Shared ptr ref++
				}
			}
		}
	}

	{ // Node deletion
		for (int k = 0; k < m_Nodes.size(); ++k) {
			if (ImNodes::IsNodeSelected(k)
				&& ImGui::IsKeyDown(ImGuiKey_Delete)
				&& k != m_SourceNode->GetID())
			{
				m_Nodes.erase(std::next(m_Nodes.begin(), k));
				m_ActiveNode = nullptr;
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

void EditorLayer::ReportError(const std::string& errStr) {
	// Tell properties panel to display the error string
	m_ActiveNode = nullptr;
	m_ErrFlag = true;
	// Set error string to displayh
	m_ErrStr = errStr;
}
