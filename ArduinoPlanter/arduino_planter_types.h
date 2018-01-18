// arduino_planter_types.h

#ifndef _ARDUINO_PLANTER_TYPES_h
#define _ARDUINO_PLANTER_TYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

typedef uint8_t pin_number;
typedef pin_number analog_in_t;
typedef pin_number digital_in_t;
typedef pin_number digital_out_t;
typedef uint32_t milliseconds_t;

#endif

