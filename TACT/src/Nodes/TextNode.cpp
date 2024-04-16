
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "TextNode.h"

TextNode::TextNode(int id) :
	Node(id),
	Text("") {}

TextNode::TextNode(int id, std::string text) :
	Node(id),
	Text(text) {}

void TextNode::RenderContent() {
	ImGui::Text(Text.c_str());
}

void TextNode::RenderProperties() {
	// ==== Title ====
	ImGui::Text("Title: ");
	ImGui::SameLine();
	ImGui::InputText("##Title", &Title);

	// ==== Terminating? ====
	ImGui::Checkbox("Terminating?", &m_TerminatingNode);

	// ==== Text ====
	ImGui::Text("Text: ");
	ImGui::SameLine();
	ImGui::InputTextMultiline("##Text", &Text);

	// ==== Input Pins ====
	ImGui::Text("Input Pins");

	// TODO: When input variables done, uncomment
	/* For now we only permit one input pin
	// Add button
	if (ImGui::Button("+##InputPins")) {
		AddInputPin();
	}
	*/

	// Display pin options
	for (std::shared_ptr<InputPin>& pin : m_InputPins) {
		// TODO: When input variables done, uncomment
		/* For now we only permit one input pin so don't delete it
		// Delete button
		ImGui::PushID(pin->GetID());
		if (ImGui::Button("-")) {
			RemoveInputPin(pin->GetID());
		}
		ImGui::PopID();
		*/

		// Display pin
		ImGui::SameLine();
		ImGui::BeginGroup();
		pin->RenderProperties();
		ImGui::EndGroup();
	}

	if (!m_TerminatingNode) {
		// ==== Output Pins ====
		ImGui::Text("Output Pins");

		// Add button
		if (ImGui::Button("+##OutputPins")) {
			AddOutputPin();
		}

		// Display pin options
		for (std::shared_ptr<OutputPin>& pin : m_OutputPins) {
			// Delete button
			ImGui::PushID(pin->GetID());
			if (ImGui::Button("-")) {
				RemoveOutputPin(pin->GetID());
			}
			ImGui::PopID();

			// Display pin
			ImGui::SameLine();
			ImGui::BeginGroup();
			pin->RenderProperties();
			ImGui::EndGroup();
		}
	}
}

const std::string& TextNode::GetPrintableContent() {
	return Text;
}
