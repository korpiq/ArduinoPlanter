// State.h

#ifndef _STATE_h
#define _STATE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Readings.h"

typedef enum input_result {
	SILENT,
	INVALID,
	REPORT,
	PUMP,
	LAMP,
	RECONFIGURED
} input_result_t;

typedef struct planter_state {
	readings_t readings;
	milliseconds_t
		lamp_start_time,
		lamp_stop_time,
		pump_start_time,
		pump_stop_time,
		air_read_time,
		report_sent_time;
	input_result_t input_result;
} planter_state_t;

#endif
