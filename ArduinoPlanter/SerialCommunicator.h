// SerialCommunicator.h

#ifndef _SERIALCOMMUNICATOR_h
#define _SERIALCOMMUNICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ArduinoJson.h"

class SerialCommunicator
{
public:
	void init(int baudRate);
	bool available();
	int read();
	void write(JsonObject*);
};

#endif
