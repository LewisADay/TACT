#pragma once

#include <memory>

#include "Node.h"

// Should probably be a singleton - perhaps
// Since we shouldn't have multiple source nodes
// This is achieved at the moment by not allowing
// the user to add any and there being one by default
// But should probably be properly enforced by code not convention

/// <summary>
/// The node to act as the source for the control flow of the Text Adventure Game
/// </summary>
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
