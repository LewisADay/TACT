
#include "imgui.h"

#include "EditorLayer.h"


void EditorLayer::OnAttach() {
}

void EditorLayer::OnDetach() {
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
	ImGui::Begin("General Kenobi");
	ImGui::ArrowButton("Test arrow button", ImGuiDir_Left);
	ImGui::End();
}
