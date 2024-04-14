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

	/// <summary>
	/// Construct an OutputPin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	OutputPin(int id);

	/// <summary>
	/// Construct an OutputPin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	/// <param name="type">Type of pin</param>
	OutputPin(int id, PinType type);

	/// <summary>
	/// Construct an OutputPin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	/// <param name="type">Type of pin</param>
	/// <param name="matchString">Sting to match against user input to choose this pin for control flow</param>
	OutputPin(int id, PinType type, std::string matchString);

	/// <summary>
	/// Render the pin (to be called by the owning node)
	/// </summary>
	virtual void Render() override;

	/// <summary>
	/// Render the pin's properties for editing in the properties window
	/// </summary>
	virtual void RenderProperties() override;

private: // Private members
	PinType m_PinType;
	std::string m_MatchString;
};
