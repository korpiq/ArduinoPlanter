// 
// 
// 

#include "DigitalWriter.h"


void DigitalWriter::init()
{
	pinMode(pin, OUTPUT);
}

void DigitalWriter::write(bool on)
{
	digitalWrite(pin, on ? HIGH : LOW);
	state = on;
}

bool DigitalWriter::isOn()
{
	return state;
}
