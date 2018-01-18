// DigitalReader.h

#ifndef _DIGITALREADER_h
#define _DIGITALREADER_h

#include "arduino_planter_types.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class DigitalReader
{
protected:
	digital_in_t pin;

public:
	DigitalReader(digital_in_t pin)
	{
		this->pin = pin;
	}

	void init();
	int read();
};

#endif

