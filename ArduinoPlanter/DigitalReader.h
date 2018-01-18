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
	void init(digital_in_t pin);
	bool read();
};

#endif

