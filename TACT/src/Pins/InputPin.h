#pragma once

#include "Pin.h"

class InputPin : public Pin {
public: // Public enums and classes
	enum PinType {
		Flow
	};

public:

	/// <summary>
	/// Construct an InputPin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	InputPin(int id);

	/// <summary>
	/// Construct an InputPin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	/// <param name="type">Type of new pin</param>
	InputPin(int id, PinType type);

	/// <summary>
	/// Render the pin (to be called by the owning node)
	/// </summary>
	void virtual Render() override;

	/// <summary>
	/// Render the pin's properties for editing in the properties window
	/// </summary>
	void virtual RenderProperties() override;

private:
	PinType m_PinType;
};
