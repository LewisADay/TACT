#pragma once

#include "Pin.h"

class OutputPin : public Pin {
public:
	OutputPin(int id);
	OutputPin(int id, PinType type);
private:
	void StartAttribute() override;
	void EndAttribute() override;
};
