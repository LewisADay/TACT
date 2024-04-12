
#include "imgui.h"

#include "imnodes.h"

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
}

void EditorLayer::RenderSidewindow() {
	ImGui::Begin("Hello There");
	ImGui::Button("Button");
	ImGui::End();
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

	// Check for new links
	int start_attr, end_attr;
	if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
		m_Links.push_back(std::make_pair(start_attr, end_attr));
	}

	ImGui::End();
}
