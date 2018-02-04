// Readings.h

#ifndef _READINGS_h
#define _READINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "arduino_planter_types.h"

typedef struct readings {
	milliseconds_t time;
	float acidity, humidity, temperature;
	bool waterOnBottom, waterOnTop, waterLevelOk;
	bool isLampOn, isPumpOn;
	bool is_remote_control;
} readings_t;

#endif
