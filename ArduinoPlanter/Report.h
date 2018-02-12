// Report.h

#ifndef _REPORT_h
#define _REPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ArduinoJson.h"
#include "Configuration.h"
#include "State.h"
#include "Decisions.h"

// buffer in stack to hold each JSON string constant in turn
#define SENDER_BUFSIZ 30

class Report
{
public:
	void sendReadings(readings_t*);
	void sendDecisions(const decisions_t * const decisions);
	void sendState(planter_state_t * state);
	void sendConfiguration(arduino_planter_configuration_t * configuration);
};

#endif
