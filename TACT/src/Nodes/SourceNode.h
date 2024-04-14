#pragma once

#include <memory>

#include "Node.h"

class SourceNode : public Node {
public: // Public methods

	/// <summary>
	/// Construct the source node
	/// </summary>
	SourceNode();

	/// <summary>
	/// Render the node (as part of the primary ImGui loop)
	/// </summary>
	virtual void Render() override;

	/// <summary>
	/// Render the node core content to be implemented by derived classes
	/// </summary>
	virtual void RenderContent() override;

	/// <summary>
	/// Render the node's properties for editing in the properties window
	/// </summary>
	virtual void RenderProperties() override;
};
