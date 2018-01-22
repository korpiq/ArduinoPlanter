// Decider.h

#ifndef _DECIDER_h
#define _DECIDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "State.h"
#include "Decisions.h"

class Decider
{
private:
	arduino_planter_configuration_t * configuration;

	char const * reasonToTurnOnLamp(planter_state_t & state);
	char const * reasonToTurnOffLamp(planter_state_t & state);

	char const * reasonToTurnOnWater(planter_state_t & state);
	char const * reasonToTurnOffWater(planter_state_t & state);

public:
	void init(arduino_planter_configuration_t&);
	void updateDecisions(planter_state_t&, decisions_t&);
	void updateLampDecision(planter_state_t&, decision_t&);
	void updatePumpDecision(planter_state_t&, decision_t&);
	void updateReportDecision(planter_state_t&, decision_t&);
};

#endif

