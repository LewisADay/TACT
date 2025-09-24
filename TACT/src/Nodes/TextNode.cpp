
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
	for (InputPin& pin : m_InputPins) {
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
		pin.RenderProperties();
		ImGui::EndGroup();
	}

	// ==== Output Pins ====
	ImGui::Text("Output Pins");

	// Add button
	if (ImGui::Button("+##OutputPins")) {
		AddOutputPin();
	}

	if (m_OutputPins.empty()) {
		ImGui::TextWrapped("No output pins. This node currently terminates the program flow.");
	}

	// Display pin options
	std::vector<int> pinsToRemove; // Almost never more than 1, but you never know
	for (OutputPin& pin : m_OutputPins) {
		// Delete button
		ImGui::PushID(pin.GetID());
		if (ImGui::Button("-")) {
			pinsToRemove.push_back(pin.GetID());
		}
		ImGui::PopID();

		// Display pin
		ImGui::SameLine();
		ImGui::BeginGroup();
		pin.RenderProperties();
		ImGui::EndGroup();
	}

	// We perform pin removal after display to avoid changing the elements of
	// the vector during interation
	for (int id : pinsToRemove) {
		RemoveOutputPin(id);
	}
}

const std::string& TextNode::GetPrintableContent() {
	return Text;
}
