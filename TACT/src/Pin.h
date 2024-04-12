#pragma once

class Pin {
public: // Public enums and classes
	enum PinType {
		Flow = 0,
		Text,
		Int
	};

public: // Public methods
	Pin(int id) :
		m_ID(id),
		m_PinType(Flow) {}

	Pin(int id, PinType type) :
		m_ID(id),
		m_PinType(type) {}

	/// <summary>
	/// Render this pin (to be called by the owning node)
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Return the pin's ID
	/// </summary>
	/// <returns>The pin's ID</returns>
	virtual int GetID();

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
