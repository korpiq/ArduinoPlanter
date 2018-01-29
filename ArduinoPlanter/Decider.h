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

	decision reasonToTurnOnLamp(planter_state_t & state);
	decision reasonToTurnOffLamp(planter_state_t & state);

	decision reasonToTurnOnWater(planter_state_t & state);
	decision reasonToTurnOffWater(planter_state_t & state);

public:
	void init(arduino_planter_configuration_t&);
	void updateDecisions(planter_state_t&, decisions_t&);
	decision updateLampDecision(planter_state_t&);
	decision updatePumpDecision(planter_state_t&);
	decision updateStateReportDecision(planter_state_t&);
	decision updateConfigurationReportDecision(planter_state_t&);
};

#endif
