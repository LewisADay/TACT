#pragma once

class Node {
public:
	Node(int id);

	void Render();
	int GetID();
private:
	int m_ID;
};
