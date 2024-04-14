#pragma once

class Pin {
public: // Public methods

	/// <summary>
	/// Construct a pin
	/// </summary>
	/// <param name="id">ID of new pin</param>
	Pin(int id);

	/// <summary>
	/// Render the pin (to be called by the owning node)
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// Render the pin's properties for editing in the properties window
	/// </summary>
	virtual void RenderProperties() = 0;

	/// <summary>
	/// Return the pin's ID
	/// </summary>
	/// <returns>The pin's ID</returns>
	virtual int GetID() const;

protected: // Protected members
	int m_ID;
};
