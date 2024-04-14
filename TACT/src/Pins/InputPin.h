#pragma once

#include "Pin.h"

class InputPin : public Pin {
public: // Public enums and classes
	enum PinType {
		Flow
	};

public:
	InputPin(int id);
	InputPin(int id, PinType type);

	void virtual Render() override;
	void virtual RenderProperties() override;

private:
	PinType m_PinType;
};
