
#include "imnodes.h"

#include "Pin.h"

void Pin::Render() {
	switch (m_PinType) {
		case Flow: RenderFlowPin(); break;
		case Text: RenderTextPin(); break;
		case Int: RenderIntPin(); break;
		default: RenderFlowPin(); break;
	}
}

int Pin::GetID() { return m_ID; }

void Pin::RenderFlowPin() {
	StartAttribute();
	EndAttribute();
}

void Pin::RenderTextPin() {
	StartAttribute();
	EndAttribute();
}

void Pin::RenderIntPin() {
	StartAttribute();
	EndAttribute();
}

void InputPin::StartAttribute() { ImNodes::BeginInputAttribute(GetID()); }

void InputPin::EndAttribute() { ImNodes::EndInputAttribute(); }

void OutputPin::StartAttribute() { ImNodes::BeginOutputAttribute(GetID()); }

void OutputPin::EndAttribute() { ImNodes::EndOutputAttribute(); }
