// Decider.h

#ifndef _DECIDER_h
#define _DECIDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "Readings.h"
#include "Decisions.h"

class Decider
{
private:
	arduino_planter_configuration_t * configuration;

public:
	void init(arduino_planter_configuration_t&);
	void updateDecisions(readings_t&, decisions_t&);
	void updateLampDecision(readings_t&, decision_t&);
	void updatePumpDecision(readings_t&, decision_t&);
};

#endif

