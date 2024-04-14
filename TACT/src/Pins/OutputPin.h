#pragma once

#include <string>

#include "Pin.h"

class OutputPin : public Pin {
public: // Public enums and classes
	enum PinType {
		UserInput,
		InvalidInput,
		Flow,
	};

public: // Public methods
	OutputPin(int id);
	OutputPin(int id, PinType type);
	OutputPin(int id, PinType type, std::string matchString);

	virtual void Render() override;
	virtual void RenderProperties() override;

private: // Private methods

private: // Private members
	PinType m_PinType;
	std::string m_MatchString;
};
