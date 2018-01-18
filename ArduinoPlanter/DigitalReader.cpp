
#include "DigitalReader.h"

void DigitalReader::init(digital_in_t pin)
{
	this->pin = pin;
	pinMode(pin, INPUT);
}

bool DigitalReader::read()
{
	return digitalRead(pin) ? true : false;
}
