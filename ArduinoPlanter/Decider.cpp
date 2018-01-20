
#include "Decider.h"

void Decider::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
}

void Decider::updateDecisions(planter_state_t & state, decisions_t & decisions)
{
	updateLampDecision(state, decisions.turn_lamp_switch);
	updatePumpDecision(state, decisions.turn_pump_switch);
}

void Decider::updateLampDecision(planter_state_t & state, decision_t & decision)
{
	if (state.readings.isLampOn)
	{
		decision.reason = reasonToTurnOffLamp(state);
		decision.doThis = decision.reason ? turn_off : NULL;
	}
	else
	{
		decision.reason = reasonToTurnOnLamp(state);
		decision.doThis = decision.reason ? turn_on : NULL;
	}
}

char const * Decider::reasonToTurnOffLamp(planter_state_t & state)
{
	return (
		state.readings.time > state.lamp_start_time + configuration->lamp_active_time
	) ? "Timeout" : NULL;
}

char const * Decider::reasonToTurnOnLamp(planter_state_t & state)
{
	return (
		state.readings.time > configuration->lamp_delay_time &&
		state.readings.time > state.pump_start_time + configuration->pump_cycle_time
		) ? "Timeout" : NULL;
}

void Decider::updatePumpDecision(planter_state_t & state, decision_t & decision)
{
	if (state.readings.isPumpOn)
	{
		decision.reason = reasonToTurnOffWater(state);
		decision.doThis = decision.reason ? turn_off : NULL;
	}
	else
	{
		decision.reason = reasonToTurnOnWater(state);
		decision.doThis = decision.reason ? turn_on : NULL;
	}
}

char const * Decider::reasonToTurnOffWater(planter_state_t & state)
{
	return state.readings.waterOnTop ? "Too much water"
		: !state.readings.waterOnBottom ? "Out of water"
		: (state.readings.time > state.pump_start_time + configuration->pump_active_time) ? "Timeout"
		: NULL;
}

char const * Decider::reasonToTurnOnWater(planter_state_t & state)
{
	bool past_initial_delay =
		state.pump_start_time || state.readings.time > configuration->pump_delay_time;
	bool full_cycle_since_last =
		state.readings.time > state.pump_start_time + configuration->pump_cycle_time;

	return (past_initial_delay && full_cycle_since_last) ? "Timeout" : NULL;
}
