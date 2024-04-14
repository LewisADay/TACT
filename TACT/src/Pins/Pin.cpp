
#include "imnodes.h"

#include "Pin.h"

Pin::Pin(int id) :
	m_ID(id) {}

/*
void Pin::RenderProperties() {
	int selection = m_PinType;
	ImGui::PushID(m_ID);
	ImGui::Combo("##PinType", &selection, "Flow\0Text\0Int");
	m_PinType = static_cast<PinType>(selection);
	ImGui::PopID();
}
*/

int Pin::GetID() const { return m_ID; }

/*
void Pin::RenderFlowPin() {
	StartAttribute();
	ImGui::Text("Flow");
	EndAttribute();
}

void Pin::RenderTextPin() {
	StartAttribute();
	// TODO Set to upstream value
	ImGui::Text("Text");
	EndAttribute();
}

void Pin::RenderIntPin() {
	StartAttribute();
	// TODO Set to upstream value, display as text for ease
	ImGui::Text("0");
	EndAttribute();
}
*/