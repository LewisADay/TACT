
#include <functional>
#include <iostream>

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imnodes.h"

#include "Node.h"

// Init Pin ID
int Node::m_PinID = 0;

Node::Node(int id) :
	m_ID(id),
	Title("New Node") {}

void Node::Render() {
	ImNodes::BeginNode(m_ID);

	// START HERE
	// TODO: Make input text work
	// TODO: Make an input area in the main node body for text if a prompt/description node
	// TODO: Make a logic area for the main node body for control flow if a logic node
	
	// Start the title bar (simple text)
	ImNodes::BeginNodeTitleBar();

	// For some reason the popup's immediately crash when you try to create them
	// I think the input text problem is related to the node environment
	/*
	// Text edit window
	if (ImGui::Button("", ImVec2(20, 20))) {
		ImGui::BeginPopup("Text Editor");

		std::string usrInput = "";
		ImGui::InputText("", &usrInput);

		if (ImGui::Button("Save")) {
			m_Title = usrInput;
		}

		ImGui::EndPopup();
	};
	*/

	ImGui::Text(Title.c_str());
	ImNodes::EndNodeTitleBar();

	// Input attributes
	for each (InputPin inPin in m_InputPins) {
		inPin.Render();
	}
	
	// Output attributes
	for each (OutputPin outPin in m_OutputPins) {
		outPin.Render();
	}

	ImNodes::EndNode();
}

int Node::GetID() const { return m_ID; }

int Node::AddInputPin() { m_InputPins.emplace_back(++m_PinID); return m_PinID; }

void Node::RemoveInputPin(int id) { RemovePin(id, m_InputPins); }

int Node::AddOutputPin() { m_OutputPins.emplace_back(++m_PinID); return m_PinID; }

void Node::RemoveOutputPin(int id) { RemovePin(id, m_OutputPins); }

template<typename TPinType, typename TEnable>
void Node::RemovePin(int id, std::vector<TPinType>& pinVec) {
	// Iterate through the pins vector, when we find one which matches the ID
	// we erase it and return
	for (int k = 0; k < pinVec.size(); ++k) {
		if (reinterpret_cast<Pin*>(&pinVec[k])->GetID() == id) {
			pinVec.erase(std::next(pinVec.begin(), k));
			return;
		}
	}

	// If we've iterated through all pins and haven't found the pin asked for we have been asked
	// to remove a non-existent pin, this should probably throw an exception or otherwise log
	// this annomalous occurence - this is left as a future idea
	// [TODO] ^ this
}
