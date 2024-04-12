#pragma once

#include "imgui.h"

#include "Walnut/Layer.h"

class EditorLayer : public Walnut::Layer {
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUIRender() override;

	void RenderSidewindow();
	void RenderMainwindow();

private:
};
