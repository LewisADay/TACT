
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
	
	// Start the title bar (simple text)
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(Title.c_str());
	ImNodes::EndNodeTitleBar();

	// Input attributes
	ImGui::BeginGroup();
	ImGui::Text("Inputs");
	for each (InputPin inPin in m_InputPins) {
		inPin.Render();
	}
	ImGui::EndGroup();
	ImGui::SameLine();

	// Main Content
	ImGui::BeginGroup();
	ImGui::Text("Content");
	RenderContent();
	ImGui::EndGroup();
	ImGui::SameLine();
	
	// Output attributes
	ImGui::BeginGroup();
	ImGui::Text("Outputs");
	for each (OutputPin outPin in m_OutputPins) {
		outPin.Render();
	}
	ImGui::EndGroup();

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
