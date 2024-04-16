
#include "imgui.h"
#include "imnodes.h"

#include "SourceNode.h"

SourceNode::SourceNode() : Node(0) {
	m_OutputPins.push_back(std::make_shared<OutputPin>(GetNextPinID(), OutputPin::PinType::Flow));
}

void SourceNode::Render() {
	ImNodes::BeginNode(m_ID);
	ImGui::Text("Source");

	ImGui::SameLine();

	// Output attributes (should be only 1 for source)
	ImGui::BeginGroup();
	for (std::shared_ptr<OutputPin>& outPin : m_OutputPins) {
		outPin->Render();
	}
	ImGui::EndGroup();

	ImNodes::EndNode();
}

void SourceNode::RenderContent() {}

void SourceNode::RenderProperties() {
	ImGui::TextWrapped("This is the source node, this is the entry point for your text adventure game!");
}
