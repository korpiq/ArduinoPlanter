
#include "Decider.h"

void Decider::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
}

void Decider::updateDecisions(planter_state_t & state, decisions_t & decisions)
{
	decisions.turn_lamp_switch = updateLampDecision(state);
	decisions.turn_pump_switch = updatePumpDecision(state);
	decisions.report_state = updateStateReportDecision(state);
	decisions.report_configuration = updateConfigurationReportDecision(state);
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
	) ? DECISION_TURN_OFF_BY_TIME : DECISION_WAIT;
}

decision Decider::reasonToTurnOnLamp(planter_state_t & state)
{
	bool full_cycle_since_last =
		(state.readings.time - state.lamp_start_time) > configuration->lamp_cycle_time;

	return full_cycle_since_last ? DECISION_TURN_ON_BY_TIME : DECISION_WAIT;
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
		: DECISION_WAIT;
}

decision Decider::reasonToTurnOnWater(planter_state_t & state)
{
	if (!state.readings.waterLevelOk)
	{
		return state.readings.waterOnTop ?
			DECISION_KEEP_OFF_WHEN_HIGH
			: DECISION_KEEP_OFF_WHEN_LOW;
	}

	bool full_cycle_since_last =
		(state.readings.time - state.pump_start_time) > configuration->pump_cycle_time;

	return full_cycle_since_last ? DECISION_TURN_ON_BY_TIME : DECISION_WAIT;
}

decision Decider::updateStateReportDecision(planter_state_t & state)
{
	if (state.input_result == REPORT_STATE)
	{
		return DECISION_REPORT_ON_REQUEST;
	}
	else if ((state.readings.time - state.report_sent_time) > configuration->report_interval)
	{
		return DECISION_REPORT_ON_TIME;
	}
	else
	{
		return DECISION_NO_ACTION;
	}
}

decision Decider::updateConfigurationReportDecision(planter_state_t & state)
{
	return
		state.input_result == RECONFIGURED ? DECISION_REPORT_WHEN_CHANGING
		: state.input_result == REPORT_CONFIGURATION ? DECISION_REPORT_ON_REQUEST
		: DECISION_NO_ACTION;
}
