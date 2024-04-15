#pragma once

#include <string>

#include "Node.h"

/// <summary>
/// Node to display text to the TAG user and use their response for control flow control
/// </summary>
class TextNode : public Node {
public: // Public methods

	/// <summary>
	/// Construct a TextNode
	/// </summary>
	/// <param name="id">ID of new node</param>
	TextNode(int id);

	/// <summary>
	/// Construct a Textnode
	/// </summary>
	/// <param name="id">IF of new node</param>
	/// <param name="text">Content of new node</param>
	TextNode(int id, std::string text);

	/// <summary>
	/// Render the node's core content
	/// </summary>
	void RenderContent() override;

	/// <summary>
	/// Render the node's properties for editing in the properties window
	/// </summary>
	void RenderProperties() override;

	/// <summary>
	/// Get a printable string of the content of the node
	/// </summary>
	/// <returns>String to print</returns>
	virtual const std::string& GetPrintableContent() override;

public: // Public members

	/// <summary>
	/// The node's display text
	/// </summary>
	std::string Text;
};
