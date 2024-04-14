
#include "imnodes.h"

#include "InputPin.h"

InputPin::InputPin(int id) : Pin(id) {}
InputPin::InputPin(int id, PinType type) : Pin(id, type) {}
void InputPin::StartAttribute() { ImNodes::BeginInputAttribute(GetID()); }
void InputPin::EndAttribute() { ImNodes::EndInputAttribute(); }
