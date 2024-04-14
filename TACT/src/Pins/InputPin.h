#pragma once

#include "Pin.h"

class InputPin : public Pin {
public:
	InputPin(int id);
	InputPin(int id, PinType type);
private:
	void StartAttribute() override;
	void EndAttribute() override;
};
