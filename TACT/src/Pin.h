#pragma once

class Pin {
public: // Public enums and classes

	enum PinType {
		Flow = 0,
		Text,
		Int,
		UsrInput,
	};

public: // Public methods

	/// <summary>
	/// Create a flow pin with id 'id'
	/// </summary>
	/// <param name="id">ID of new pin</param>
	Pin(int id);

	/// <summary>
	/// Create a pin with id 'id' and of type 'type'
	/// </summary>
	/// <param name="id">ID of new pin</param>
	/// <param name="type">Type of new pin</param>
	Pin(int id, PinType type);

	/// <summary>
	/// Render the pin (to be called by the owning node)
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Render the pin's properties for editing in the properties window
	/// </summary>
	virtual void RenderProperties();

	/// <summary>
	/// Return the pin's ID
	/// </summary>
	/// <returns>The pin's ID</returns>
	virtual int GetID() const;

private: // Private methods
	virtual void StartAttribute() = 0;
	virtual void EndAttribute() = 0;
	void RenderFlowPin();
	void RenderTextPin();
	void RenderIntPin();

private: // Private members
	int m_ID;
	PinType m_PinType;
};

class InputPin : public Pin {
public:
	InputPin(int id) : Pin(id) {}
	InputPin(int id, PinType type) : Pin(id, type) {}
private:
	void StartAttribute() override;
	void EndAttribute() override;
};

class OutputPin : public Pin {
public:
	OutputPin(int id) : Pin(id) {}
	OutputPin(int id, PinType type) : Pin(id, type) {}
private:
	void StartAttribute() override;
	void EndAttribute() override;
};
