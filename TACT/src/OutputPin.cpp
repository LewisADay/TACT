
#include "imnodes.h"

#include "OutputPin.h"

OutputPin::OutputPin(int id) : Pin(id) {}
OutputPin::OutputPin(int id, PinType type) : Pin(id, type) {}
void OutputPin::StartAttribute() { ImNodes::BeginOutputAttribute(GetID()); }
void OutputPin::EndAttribute() { ImNodes::EndOutputAttribute(); }
