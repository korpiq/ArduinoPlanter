
#include "DigitalWriter.h"

void DigitalWriter::init(digital_out_t pin)
{
	this->pin = pin;
	this->state = false;
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
