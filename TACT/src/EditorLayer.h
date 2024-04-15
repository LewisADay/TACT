#pragma once

#include <vector>

#include "imgui.h"

#include "Walnut/Layer.h"
#include "Nodes/Node.h"
#include "Nodes/SourceNode.h"

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

	/// <summary>
	/// Save the state of the editor and open a save dialog
	/// </summary>
	void Save();

	/// <summary>
	/// Open a file load dialog and load the editor state from the selected file
	/// </summary>
	void Load();

	/// <summary>
	/// Compile the game described in the editor
	/// </summary>
	void GenerateGame();

private:
	void RenderSidewindow();
	void RenderMainwindow();
	void LinkOperations();
	void SelectedNodeManagement();
	void RightClickMenu();
	int GetNextNodeID();
	void NewNode(const NodeType& type);
	void NewTextNode();

private:

	std::vector<std::shared_ptr<Node>> m_Nodes;
	std::shared_ptr<Node> m_ActiveNode;
	std::vector<std::pair<int, int>> m_Links;
	std::shared_ptr<SourceNode> m_SourceNode;
	int _NodeID = 0; // Not m_ as should only be used if you know what you're doing, use GetNextNodeID().
};
