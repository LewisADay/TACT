
#include "imgui.h"

#include "imnodes.h"

#include "EditorLayer.h"


void EditorLayer::OnAttach() {
	ImNodes::CreateContext();

	m_Nodes.emplace_back(1);
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

	for each (Node node in m_Nodes) {
		node.Render();
	}

	ImNodes::EndNodeEditor();
	ImGui::End();
}
