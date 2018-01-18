// DigitalWriter.h

#ifndef _DIGITALWRITER_h
#define _DIGITALWRITER_h

#include "arduino_planter_types.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DigitalWriter
{
protected:
	digital_out_t pin;
	bool state;

public:
	DigitalWriter(digital_out_t pin)
	{
		this->pin = pin;
		this->state = false;
	}

	void init();
	void write(bool on);
	bool isOn();
};

#endif
