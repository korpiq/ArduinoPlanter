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
		lamp_change_time,
		pump_change_time;
} planter_state_t;

void initPlanterState(planter_state_t * state);

#endif
