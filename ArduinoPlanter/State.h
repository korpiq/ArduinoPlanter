// State.h

#ifndef _STATE_h
#define _STATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Readings.h"

typedef struct planter_state {
	readings_t readings;
	milliseconds_t
		lamp_start_time,
		lamp_stop_time,
		pump_start_time,
		pump_stop_time,
		air_read_time,
		report_sent_time;
} planter_state_t;

#endif
