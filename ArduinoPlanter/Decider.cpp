
#include "Decider.h"

void Decider::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
}

void Decider::updateDecisions(planter_state_t & state, decisions_t & decisions)
{
	updateLampDecision(state, decisions.turn_lamp_switch);
	updatePumpDecision(state, decisions.turn_pump_switch);
	updateReportDecision(state, decisions.send_report);
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
		(state.readings.time - state.lamp_start_time) > configuration->lamp_active_time
	) ? "Timeout" : NULL;
}

char const * Decider::reasonToTurnOnLamp(planter_state_t & state)
{
	if (state.lamp_start_time) // has been started before
	{
		bool full_cycle_since_last =
			(state.readings.time - state.lamp_start_time) > configuration->lamp_cycle_time;

		return full_cycle_since_last ? "Time to turn lamp on again" : NULL;
	}
	else // wait for first start time
	{
		bool past_initial_delay =
			(state.readings.time > configuration->lamp_delay_time);

		return past_initial_delay ? "Past initial delay" : NULL;
	}
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
		: ((state.readings.time - state.pump_start_time) > configuration->pump_active_time) ?
			"Timeout"
		: NULL;
}

char const * Decider::reasonToTurnOnWater(planter_state_t & state)
{
	if (!state.readings.waterLevelOk)
	{
		return NULL;
	}

	if (state.pump_start_time) // has been started before
	{
		bool full_cycle_since_last =
			(state.readings.time - state.pump_start_time) > configuration->pump_cycle_time;

		return full_cycle_since_last ? "Time to turn pump on again" : NULL;
	}
	else // wait for first start time
	{
		bool past_initial_delay =
			state.pump_start_time || (state.readings.time > configuration->pump_delay_time);

		return (past_initial_delay) ? "Past initial delay" : NULL;
	}
}

void Decider::updateReportDecision(planter_state_t & state, decision_t & decision)
{
	if (state.readings.communication)
	{
		decision.doThis = do_once;
		decision.reason = "Communication request received";
	}
	else if ((state.readings.time - state.report_sent_time) > configuration->report_interval)
	{
		decision.doThis = do_once;
		decision.reason = "Time to report";
	}
	else
	{
		decision.doThis = NULL;
		decision.reason = NULL;
	}
}
