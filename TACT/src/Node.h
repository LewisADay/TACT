#pragma once

#include <vector>
#include <string>

#include "Pin.h"

/// <summary>
/// A node on the flow map
/// </summary>
class Node {
public: // Public methods

	/// <summary>
	/// Construct a node with ID id.
	/// </summary>
	/// <param name="id"></param>
	Node(int id);

	/// <summary>
	/// Render the node (as part of the primary ImGui loop)
	/// </summary>
	void Render();

	/// <summary>
	/// Retrieve the unique node ID
	/// </summary>
	/// <returns>The node's ID</returns>
	int GetID() const;

	/// <summary>
	/// Add an input pin
	/// </summary>
	/// <returns>The pin ID of the newly created input pin</returns>
	int AddInputPin();

	/// <summary>
	/// Remove an input pin by ID
	/// </summary>
	/// <param name="id">The ID of the input pin to remove</param>
	void RemoveInputPin(int id);

	/// <summary>
	/// Add an output pin
	/// </summary>
	/// <returns>The pin ID of the newly created output pin</returns>
	int AddOutputPin();

	/// <summary>
	/// Remove an output pin by ID
	/// </summary>
	/// <param name="id">The ID of the output pin to remove</param>
	void RemoveOutputPin(int id);

public: // Public members

	/// <summary>
	/// The title of the node
	/// </summary>
	std::string Title;

private: // Private methods

	// Some SFINAE because one ought to show off to prospective employers I suppose
	// Not sure it's the best suited to this use case but here is a use of it
	
	// Enabled only if the vector is a vector of objects of a class derived from Pin
	template<typename TPinType, typename TEnable = std::enable_if<std::is_base_of_v<Pin, TPinType>>>
	void RemovePin(int id, std::vector<TPinType>& pinVec);

private: // Private static members

	/// <summary>
	/// Shared incrementing pin ID amungst Nodes (pin ids must be globally unique)
	/// </summary>
	static int m_PinID;

	/// <summary>
	/// How long do we permit the title to be (in characters)
	/// </summary>
	static const size_t m_TitleLength = 128;

private: // Private members

	/// <summary>
	/// Unique node ID
	/// </summary>
	int m_ID;

	std::vector<InputPin> m_InputPins;
	std::vector<OutputPin> m_OutputPins;
};
