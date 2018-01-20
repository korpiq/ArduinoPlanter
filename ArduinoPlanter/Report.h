// Report.h

#ifndef _REPORT_h
#define _REPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ArduinoJson.h"
#include "Readings.h"

class Report
{
	StaticJsonBuffer<500> jsonBuffer;
public:
	JsonObject & contents = jsonBuffer.createObject();
	void setReadings(readings_t*);
	void send();
};

#endif

