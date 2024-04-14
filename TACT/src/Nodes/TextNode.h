#pragma once

#include <string>

#include "Node.h"

class TextNode : public Node {
public: // Public methods
	TextNode(int id);
	TextNode(int id, std::string text);

	void RenderContent() override;
	void RenderProperties() override;

public: // Public members
	std::string Text;
};
