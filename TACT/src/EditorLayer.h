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

	void RenderSidewindow();
	void RenderMainwindow();

private:

	std::vector<Node> m_Nodes;
	std::vector<std::pair<int, int>> m_Links;
};
