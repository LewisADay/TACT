#pragma once

#include <vector>

#include "imgui.h"

#include "Walnut/Layer.h"
#include "Node.h"

class EditorLayer : public Walnut::Layer {
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUIRender() override;

private:
	void RenderSidewindow();
	void RenderActiveNodeData();
	void RenderMainwindow();
	void CheckLinks();
	void UpdateSidewindow();

private:

	std::vector<Node> m_Nodes;
	Node* m_ActiveNode; // TODO: Think of a way to smart ptr this/otherwise refactor to avoid raw ptrs
	//int m_ActiveNode;
	std::vector<std::pair<int, int>> m_Links;
	std::string tmp = "";
};
