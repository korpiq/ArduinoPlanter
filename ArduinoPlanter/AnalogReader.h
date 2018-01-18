// AnalogReader.h

#ifndef _ANALOGREADER_h
#define _ANALOGREADER_h

#include "arduino_planter_types.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class AnalogReader
{
protected:
	analog_in_t pin;

public:
	AnalogReader(analog_in_t pin)
	{
		this->pin = pin;
	}

	int read();
};

#endif

