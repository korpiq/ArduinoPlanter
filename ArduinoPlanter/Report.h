// Report.h

#ifndef _REPORT_h
#define _REPORT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ArduinoJson.h"
#include "State.h"
#include "Decisions.h"

class Report
{
public:
	JsonObject * jsonObject = NULL;
	void setReadings(readings_t*);
	void setDecisions(decisions_t * decisions);
	void setState(planter_state_t * state);
	void send();
};

#endif

