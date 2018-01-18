
#include "AnalogReader.h"

int AnalogReader::read()
{
	return analogRead(pin);
}
