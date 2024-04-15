
#include <functional>
#include <iostream>

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"
#include "imnodes.h"

#include "Node.h"

Node::Node(int id) :
	m_ID(id),
	Title("New Node"),
	m_ContentStr("") {}

void Node::Render() {

	ImNodes::BeginNode(m_ID);
	
	// Start the title bar (simple text)
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(Title.c_str());
	ImNodes::EndNodeTitleBar();

	// Input attributes
	ImGui::BeginGroup();
	for (std::shared_ptr<InputPin>& inPin : m_InputPins) {
		inPin->Render();
	}
	ImGui::EndGroup();

	ImGui::SameLine();
	//ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	//ImGui::SameLine();

	// Main Content
	ImGui::BeginGroup();
	RenderContent();
	ImGui::EndGroup();
	
	ImGui::SameLine();
	ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	ImGui::SameLine();

	// Output attributes
	ImGui::BeginGroup();
	for (std::shared_ptr<OutputPin>& outPin : m_OutputPins) {
		outPin->Render();
	}
	ImGui::EndGroup();

	ImNodes::EndNode();
}

int Node::GetID() const { return m_ID; }

const std::vector<std::shared_ptr<InputPin>>& Node::GetInputPins() const { return m_InputPins; }

const std::vector<std::shared_ptr<OutputPin>>& Node::GetOutputPins() const { return m_OutputPins; }

int Node::AddInputPin() {
	int id = GetNextPinID();
	m_InputPins.push_back(std::make_shared<InputPin>(id));
	return id;
}

void Node::RemoveInputPin(const int& id) { RemovePin(id, m_InputPins); }

int Node::AddOutputPin() {
	int id = GetNextPinID();
	m_OutputPins.push_back(std::make_shared<OutputPin>(id));
	return id;
}

void Node::RemoveOutputPin(const int& id) { RemovePin(id, m_OutputPins); }

const std::string& Node::GetPrintableContent() {
	m_ContentStr = "";
	return m_ContentStr;
}

int Node::GetNextPinID() { return ++_PinID; }

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
	// TODO ^ this
}
