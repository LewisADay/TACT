
#include "imnodes.h"

#include "InputPin.h"

InputPin::InputPin(int id) :
	Pin(id),
	m_PinType(Flow) {}

InputPin::InputPin(int id, PinType type) :
	Pin(id),
	m_PinType(type) {}

void InputPin::Render() {
	ImNodes::BeginInputAttribute(m_ID);

	switch (m_PinType) {
	case Flow:
		ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));
		break; // We don't add text or anything to flow nodes
		// TODO
		// Probably add an exception for default condition - we are a pin type that isn't defined
		// or hasn't been addded to this swtich
	}

	ImNodes::EndInputAttribute();
}

void InputPin::RenderProperties() {
	int selection = m_PinType;
	ImGui::PushID(m_ID);
	ImGui::Combo("##PinType", &selection, "Flow\0");
	m_PinType = static_cast<PinType>(selection);
	ImGui::PopID();
}
