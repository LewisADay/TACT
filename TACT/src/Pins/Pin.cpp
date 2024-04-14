
#include "imnodes.h"

#include "Pin.h"

Pin::Pin(int id) :
	m_ID(id) {}

int Pin::GetID() const { return m_ID; }
