
#include "Decider.h"

void Decider::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
}

void Decider::updateDecisions(planter_state_t & state, decisions_t & decisions)
{
	decisions.turn_lamp_switch = updateLampDecision(state);
	decisions.turn_pump_switch = updatePumpDecision(state);
	decisions.send_report = updateReportDecision(state);
}

decision Decider::updateLampDecision(planter_state_t & state)
{
	if (state.input_result == LAMP)
	{
		return state.readings.isLampOn ? DECISION_TURN_OFF_BY_REQUEST : DECISION_TURN_ON_BY_REQUEST;
	}
	else if (state.readings.isLampOn)
	{
		return reasonToTurnOffLamp(state);
	}
	else
	{
		return reasonToTurnOnLamp(state);
	}
}

decision Decider::reasonToTurnOffLamp(planter_state_t & state)
{
	return (
		(state.readings.time - state.lamp_start_time) > configuration->lamp_active_time
	) ? DECISION_TURN_OFF_BY_TIME : DECISION_NO_ACTION;
}

decision Decider::reasonToTurnOnLamp(planter_state_t & state)
{
	if (state.lamp_start_time) // has been started before
	{
		bool full_cycle_since_last =
			(state.readings.time - state.lamp_start_time) > configuration->lamp_cycle_time;

		return full_cycle_since_last ? DECISION_TURN_ON_BY_TIME : DECISION_NO_ACTION;
	}
	else // wait for first start time
	{
		bool past_initial_delay =
			(state.readings.time > configuration->lamp_delay_time);

		return past_initial_delay ? DECISION_TURN_ON_BY_TIME : DECISION_NO_ACTION;
	}
}

decision Decider::updatePumpDecision(planter_state_t & state)
{
	if (state.input_result == PUMP)
	{
		return state.readings.isPumpOn ? DECISION_TURN_OFF_BY_REQUEST : DECISION_TURN_ON_BY_REQUEST;
	}
	else if (state.readings.isPumpOn)
	{
		return reasonToTurnOffWater(state);
	}
	else
	{
		return reasonToTurnOnWater(state);
	}
}

decision Decider::reasonToTurnOffWater(planter_state_t & state)
{
	return state.readings.waterOnTop ? DECISION_TURN_OFF_WHEN_WATER_HIGH
		: !state.readings.waterOnBottom ? DECISION_TURN_OFF_WHEN_WATER_LOW
		: ((state.readings.time - state.pump_start_time) > configuration->pump_active_time) ?
			DECISION_TURN_OFF_BY_TIME
		: DECISION_NO_ACTION;
}

decision Decider::reasonToTurnOnWater(planter_state_t & state)
{
	if (!state.readings.waterLevelOk)
	{
		if (state.readings.waterOnTop)
			return DECISION_KEEP_OFF_WHEN_HIGH;
		return DECISION_KEEP_OFF_WHEN_HIGH;
	}

	if (state.pump_start_time) // has been started before
	{
		bool full_cycle_since_last =
			(state.readings.time - state.pump_start_time) > configuration->pump_cycle_time;

		return full_cycle_since_last ? DECISION_TURN_ON_BY_TIME : DECISION_WAIT;
	}
	else // wait for first start time
	{
		bool past_initial_delay =
			state.pump_start_time || (state.readings.time > configuration->pump_delay_time);

		return (past_initial_delay) ? DECISION_TURN_ON_BY_TIME : DECISION_WAIT;
	}
}

decision Decider::updateReportDecision(planter_state_t & state)
{
	if (state.input_result == RECONFIGURED)
	{
		return DECISION_REPORT_CONFIGURATION_WHEN_CHANGING;
	}
	else if(state.input_result == REPORT_CONFIGURATION)
	{
		return DECISION_REPORT_CONFIGURATION_ON_REQUEST;
	}
	else if (state.input_result == REPORT_STATE)
	{
		return DECISION_REPORT_STATE_ON_REQUEST;
	}
	else if ((state.readings.time - state.report_sent_time) > configuration->report_interval)
	{
		return DECISION_REPORT_STATE_ON_TIME;
	}
	else
	{
		return DECISION_NO_ACTION;
	}
}
