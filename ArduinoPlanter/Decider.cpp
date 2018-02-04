
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
	if (state.input_result == REQUEST_LAMP)
	{
		return state.readings.is_lamp_on ? DECISION_TURN_OFF_BY_REQUEST : DECISION_TURN_ON_BY_REQUEST;
	}
	else if (state.readings.is_remote_control)
	{
		return DECISION_WAIT_FOR_COMMAND;
	}
	else if (state.readings.is_lamp_on)
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
	if (state.readings.water_on_top) // ride over troubled water
	{
		return state.readings.is_pump_on ?
			DECISION_TURN_OFF_WHEN_WATER_HIGH
			: DECISION_KEEP_OFF_WHEN_HIGH;
	}
	else if (! state.readings.water_on_bottom)
	{
		return state.readings.is_pump_on ?
			DECISION_TURN_OFF_WHEN_WATER_LOW
			: DECISION_KEEP_OFF_WHEN_LOW;
	}
	else if (state.input_result == REQUEST_PUMP)
	{
		return state.readings.is_pump_on ? DECISION_TURN_OFF_BY_REQUEST : DECISION_TURN_ON_BY_REQUEST;
	}
	else if (state.readings.is_remote_control)
	{
		return DECISION_WAIT_FOR_COMMAND;
	}
	else if (state.readings.is_pump_on)
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
	bool has_run_long_enough = 
		(state.readings.time - state.pump_start_time) > configuration->pump_active_time;

	return has_run_long_enough ? DECISION_TURN_OFF_BY_TIME : DECISION_WAIT;
}

decision Decider::reasonToTurnOnWater(planter_state_t & state)
{
	bool full_cycle_since_last =
		(state.readings.time - state.pump_start_time) > configuration->pump_cycle_time;

	return full_cycle_since_last ? DECISION_TURN_ON_BY_TIME : DECISION_WAIT;
}

decision Decider::updateStateReportDecision(planter_state_t & state)
{
	if (state.input_result == REQUEST_REPORT_STATE)
	{
		return DECISION_REPORT_ON_REQUEST;
	}
	else if (state.readings.is_remote_control)
	{
		return DECISION_WAIT_FOR_COMMAND;
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
		state.input_result == REQUEST_RECONFIGURE ? DECISION_REPORT_WHEN_CHANGING
		: state.input_result == REQUEST_REPORT_CONFIGURATION ? DECISION_REPORT_ON_REQUEST
		: DECISION_NO_ACTION;
}
