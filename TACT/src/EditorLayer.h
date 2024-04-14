#pragma once

#include <vector>

#include "imgui.h"

#include "Walnut/Layer.h"
#include "Nodes/Node.h"

class EditorLayer : public Walnut::Layer {
public: // Public enums and classes

	enum NodeType {
		Text,
	};

public:

	/// <summary>
	/// Triggered when layer initially attached to renderer
	/// </summary>
	virtual void OnAttach() override;

	/// <summary>
	/// Triggered when layer detached from renderer
	/// </summary>
	virtual void OnDetach() override;

	/// <summary>
	/// Called every UI render pass (basically once a frame)
	/// </summary>
	virtual void OnUIRender() override;

private:
	void RenderSidewindow();
	void RenderMainwindow();
	void LinkOperations();
	void SelectedNodeManagement();
	void RightClickMenu();
	int GetNextNodeID();
	void NewNode(NodeType type);
	void NewTextNode();

private:

	std::vector<std::shared_ptr<Node>> m_Nodes;
	std::shared_ptr<Node> m_ActiveNode;
	std::vector<std::pair<int, int>> m_Links;
	int _NodeID; // Not m_ as should only be used if you know what you're doing, use GetNextNodeID().
};
