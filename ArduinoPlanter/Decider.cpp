// 
// 
// 

#include "Decider.h"

void Decider::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
}

void Decider::updateDecisions(readings_t & readings, decisions_t & decisions)
{
	updateLampDecision(readings, decisions.turn_lamp_switch);
	updatePumpDecision(readings, decisions.turn_pump_switch);
}

void Decider::updateLampDecision(readings_t & readings, decision_t & decision)
{
	decision.doThis = NULL;
	decision.reason = "Not implemented yet, needs time keeping";
}

void Decider::updatePumpDecision(readings_t & readings, decision_t & decision)
{
	if (readings.isPumpOn)
	{
		if (readings.waterOnTop)
		{
			decision.doThis = turn_off;
			decision.reason = "Too much water";
		}
		else if (!readings.waterOnBottom)
		{
			decision.doThis = turn_off;
			decision.reason = "Out of water";
		}
		else
		{
			decision.doThis = NULL;
			decision.reason = "Water level adequate";
		}
	}
	else
	{
		decision.doThis = NULL;
		decision.reason = "Not implemented yet, needs time keeping";
	}
}
