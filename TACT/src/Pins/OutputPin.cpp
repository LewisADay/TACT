
#include "imnodes.h"
#include "misc/cpp/imgui_stdlib.h"

#include "OutputPin.h"

// TODO
// Make generic the retrieval of the magic strings
// e.g. when constructing the combo box (drop down) in render properties
// we should construct the options string rather than rely on the constant
// one there being accurate
// This also applies for the display of the set PinType in render, those
// ImGui::Text calls should be automated

OutputPin::OutputPin(int id) :
	Pin(id),
	m_PinType(UserInput),
	m_MatchString("") {}

OutputPin::OutputPin(int id, PinType type) :
	Pin(id),
	m_PinType(type),
	m_MatchString("") {}

OutputPin::OutputPin(int id, PinType type, std::string matchString) :
	Pin(id),
	m_PinType(type),
	m_MatchString(matchString) {}

void OutputPin::Render() {
	ImNodes::BeginOutputAttribute(m_ID);

	switch (m_PinType) {
	case UserInput:
		if (m_MatchString.empty()) { ImGui::Text("Set User Input"); }
		else { ImGui::Text(m_MatchString.c_str()); }
		break;
	case InvalidInput:
		ImGui::Text("Invalid Input");
		break;
	case Flow:
		break;
	// TODO
	// Probably add an exception for default condition - we are a pin type that isn't defined
	// or hasn't been addded to this swtich
	}

	ImNodes::EndOutputAttribute();
}

void OutputPin::RenderProperties() {
	ImGui::PushID(m_ID);

	{// Select the type of the pin
		int selection = m_PinType;
		// TODO: Implement invalid input flow control (TAG Generation update needed to support)
		// For now we disallow flow control from the invalid input
		//ImGui::Combo("##PinType", &selection, "User Input\0Invalid Input");
		ImGui::Combo("##PinType", &selection, "User Input");
		m_PinType = static_cast<PinType>(selection);
	}

	// If a usr output pin, what user response will this map to
	if (m_PinType == UserInput) {
		ImGui::Text("Match Text: ");
		ImGui::SameLine();
		ImGui::InputText("##MatchText", &m_MatchString);
	}

	ImGui::PopID();
}

const OutputPin::PinType& OutputPin::GetPinType() const { return m_PinType; }

const std::string& OutputPin::GetMatchString() const { return m_MatchString; }
