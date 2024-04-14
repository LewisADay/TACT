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
	void RenderMainwindow();
	void CheckLinks();
	void CheckForNewSelectedNode();

private:

	std::vector<std::shared_ptr<Node>> m_Nodes;
	std::shared_ptr<Node> m_ActiveNode;
	std::vector<std::pair<int, int>> m_Links;
	std::string tmp = "";
};
