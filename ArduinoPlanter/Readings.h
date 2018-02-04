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
	bool water_on_bottom, water_on_top, water_level_ok;
	bool is_lamp_on, is_pump_on;
	bool is_remote_control;
} readings_t;

#endif
