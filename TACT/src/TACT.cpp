#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

//#include "Walnut/Image.h"

#include "EditorLayer.h"

Walnut::Application* Walnut::CreateApplication(int argc, char** argv) {

	Walnut::ApplicationSpecification spec;
	spec.Name = "Text Adventure Creation Tool";

	Walnut::Application* app = new Walnut::Application(spec);

	std::shared_ptr<EditorLayer> editorLayer = std::make_shared<EditorLayer>();
	app->PushLayer(editorLayer);
	app->SetMenubarCallback([app, editorLayer]() {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Save")) {
				editorLayer->Save();
			}
			if (ImGui::MenuItem("Load")) {
				editorLayer->Load();
			}
			if (ImGui::MenuItem("Generate Game")) {
				editorLayer->GenerateGame();
			}
			if (ImGui::MenuItem("Exit")) {
				app->Close();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About")) {
			ImGui::Text("Author: Lewis Day");
			ImGui::Text("Version: 0.1");
			ImGui::Text("GitHub: https://www.github.com/LewisADay/TACT");
			ImGui::EndMenu();
		}
	});
	return app;
}
