
#include <iostream>

#include "imgui.h"
#include "imnodes.h"
#include "misc/cpp/imgui_stdlib.h"

#include "EditorLayer.h"


void EditorLayer::OnAttach() {
	ImNodes::CreateContext();

	m_Nodes.emplace_back(1);
	m_Nodes[0].AddInputPin();
	m_Nodes[0].AddOutputPin();
	m_Nodes.emplace_back(2);
	m_Nodes[1].AddInputPin();
	m_Nodes[1].AddOutputPin();
}

void EditorLayer::OnDetach() {
	ImNodes::DestroyContext();
}

void EditorLayer::OnUIRender() {
	RenderSidewindow();
	RenderMainwindow();
	CheckLinks();
	UpdateSidewindow();
}

void EditorLayer::RenderSidewindow() {
	ImGui::Begin("Hello There");

	if (m_ActiveNode) {
		RenderActiveNodeData();
	}
	else {
		ImGui::Text("Select a node to customize it.");
	}
	
	ImGui::End();
}

void EditorLayer::RenderActiveNodeData() {

	// Don't be dereferencing things we shouldn't be dereferencing
	assert(m_ActiveNode != nullptr);

	// Maybe remove - uneccessary extra area title perhaps
	// maybe just add vspace instead; UI/UX question, not going to focus on it
	ImGui::Text("Node Selected");

	// Title
	ImGui::Text("Title: ");
	ImGui::SameLine();
	ImGui::InputText("##", &m_ActiveNode->Title);
}

void EditorLayer::RenderMainwindow() {
	ImGui::Begin("Editor");
	ImNodes::BeginNodeEditor();

	// Render the nodes
	for each (Node node in m_Nodes) {
		node.Render();
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

void EditorLayer::UpdateSidewindow() {
	int nodeID;
	if (ImNodes::IsNodeHovered(&nodeID) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		for (int k = 0; k < m_Nodes.size(); ++k) {
			if (m_Nodes[k].GetID() == nodeID) {
				m_ActiveNode = &m_Nodes[k];
			}
		}
	}
}
