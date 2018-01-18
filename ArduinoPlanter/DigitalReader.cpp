
#include "DigitalReader.h"

void DigitalReader::init()
{
	pinMode(pin, INPUT);
}

int DigitalReader::read()
{
	return digitalRead(pin);
}
