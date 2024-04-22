#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Pins/InputPin.h"
#include "Pins/OutputPin.h"

/// <summary>
/// A node on the flow map
/// </summary>
class Node {
public: // Public methods

	/// <summary>
	/// Construct a node
	/// </summary>
	/// <param name="id">ID of new node</param>
	Node(int id);

	/// <summary>
	/// Render the node (as part of the primary ImGui loop)
	/// </summary>
	virtual void Render();

	/// <summary>
	/// Retrieve the unique node ID
	/// </summary>
	/// <returns>The node's ID</returns>
	int GetID() const;

	/// <summary>
	/// Retrieve a const ref to the input pins vector
	/// </summary>
	/// <returns>A vector of the input pins of this node</returns>
	const std::vector<std::shared_ptr<InputPin>>& GetInputPins() const;

	/// <summary>
	/// Retrieve a const ref to the output pins vector
	/// </summary>
	/// <returns>A vector of the output pins of this node</returns>
	const std::vector<std::shared_ptr<OutputPin>>& GetOutputPins() const;

	/// <summary>
	/// Add an input pin
	/// </summary>
	/// <returns>The pin ID of the newly created input pin</returns>
	int AddInputPin();

	/// <summary>
	/// Add an input pin with the given id
	/// </summary>
	/// <param name="id">ID of the new pin</param>
	/// <returns>If the pin was able to be created with the given id</returns>
	bool AddInputPin(int id);

	/// <summary>
	/// Remove an input pin by ID
	/// </summary>
	/// <param name="id">The ID of the input pin to remove</param>
	void RemoveInputPin(const int& id);

	/// <summary>
	/// Add an output pin
	/// </summary>
	/// <returns>The pin ID of the newly created output pin</returns>
	int AddOutputPin();

	/// <summary>
	/// Add an output text pin
	/// </summary>
	/// <param name="content">Pin content</param>
	/// <returns>The pin ID of the newly created output pin</returns>
	int AddOutputTextPin(const std::string& content);

	/// <summary>
	/// Remove an output pin by ID
	/// </summary>
	/// <param name="id">The ID of the output pin to remove</param>
	void RemoveOutputPin(const int& id);

	/// <summary>
	/// Render the node's core content
	/// </summary>
	virtual void RenderContent() = 0;

	/// <summary>
	/// Render the node's properties for editing in the properties window
	/// </summary>
	virtual void RenderProperties() = 0;

	/// <summary>
	/// Get a printable string of the content of the node
	/// </summary>
	/// <returns>String to print</returns>
	virtual const std::string& GetPrintableContent();

	/// <summary>
	/// Is this node terminating
	/// </summary>
	/// <returns>If this node terminates the TAG</returns>
	virtual bool IsTerminating();

public: // Public members

	/// <summary>
	/// The title of the node
	/// </summary>
	std::string Title;

protected: // Protected static methods

	/// <summary>
	/// Generate the next pin ID
	/// </summary>
	/// <returns>New valid ID for a Pin</returns>
	static int GetNextPinID();

protected: // Protected members

	/// <summary>
	/// Unique node ID
	/// </summary>
	int m_ID;

	bool m_TerminatingNode;
	std::string m_ContentStr;
	std::vector<std::shared_ptr<InputPin>> m_InputPins;
	std::vector<std::shared_ptr<OutputPin>> m_OutputPins;
	
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
	static inline int _PinID = 0; // Not m_ as access should be via GetNextPinID
};
