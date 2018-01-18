
#include "AnalogReader.h"

void AnalogReader::init(analog_in_t pin)
{
	this->pin = pin;
}

int AnalogReader::read()
{
	return analogRead(pin);
}
