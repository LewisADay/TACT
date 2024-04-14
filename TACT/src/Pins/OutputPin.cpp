
#include "imnodes.h"

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
	case UserInput: ImGui::Text("User Input"); break;
	case InvalidInput: ImGui::Text("Invalid Input"); break;
	// TODO
	// Probably add an exception for default condition - we are a pin type that isn't defined
	// or hasn't been addded to this swtich
	}

	ImNodes::EndOutputAttribute();
}

void OutputPin::RenderProperties() {
	int selection = m_PinType;
	ImGui::PushID(m_ID);
	ImGui::Combo("##PinType", &selection, "User Input\0Invalid Input");
	m_PinType = static_cast<PinType>(selection);
	ImGui::PopID();
}