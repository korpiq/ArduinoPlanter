
#include "DigitalReader.h"

void DigitalReader::init(digital_in_t pin)
{
	this->pin = pin;
	pinMode(pin, INPUT);
}

int DigitalReader::read()
{
	return digitalRead(pin);
}
