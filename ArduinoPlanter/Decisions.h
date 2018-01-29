#pragma once

enum actions
{
	DO_NOTHING,
	DO_TURN_ON,
	DO_TURN_OFF,
	DO_REPORT_STATE,
	DO_REPORT_CONFIGURATION,
	NUMBER_OF_ACTIONS
};

extern const char * const action_names[NUMBER_OF_ACTIONS];

enum reasons
{
	REASON_DOING_FINE,
	REASON_REQUEST,
	REASON_TIME,
	REASON_WATER_LOW,
	REASON_WATER_HIGH,
	REASON_CHANGE,
	NUMBER_OF_REASONS
};

extern const char * const reason_descriptions[NUMBER_OF_REASONS];

enum decision
{
	DECISION_NO_ACTION = (REASON_DOING_FINE << 4) + DO_NOTHING,
	DECISION_WAIT = (REASON_TIME << 4) + DO_NOTHING,
	DECISION_KEEP_OFF_WHEN_LOW = (REASON_WATER_LOW << 4) + DO_NOTHING,
	DECISION_KEEP_OFF_WHEN_HIGH = (REASON_WATER_HIGH << 4) + DO_NOTHING,
	DECISION_TURN_ON_BY_REQUEST = (REASON_REQUEST << 4) + DO_TURN_ON,
	DECISION_TURN_OFF_BY_REQUEST = (REASON_REQUEST << 4) + DO_TURN_OFF,
	DECISION_TURN_ON_BY_TIME = (REASON_TIME << 4) + DO_TURN_ON,
	DECISION_TURN_OFF_BY_TIME = (REASON_TIME << 4) + DO_TURN_OFF,
	DECISION_TURN_OFF_WHEN_WATER_LOW = (REASON_WATER_LOW << 4) + DO_TURN_OFF,
	DECISION_TURN_OFF_WHEN_WATER_HIGH = (REASON_WATER_HIGH << 4) + DO_TURN_OFF,
	DECISION_REPORT_CONFIGURATION_ON_REQUEST = (REASON_REQUEST << 4) + DO_REPORT_CONFIGURATION,
	DECISION_REPORT_CONFIGURATION_WHEN_CHANGING = (REASON_CHANGE << 4) + DO_REPORT_CONFIGURATION,
	DECISION_REPORT_STATE_ON_REQUEST = (REASON_REQUEST << 4) + DO_REPORT_STATE,
	DECISION_REPORT_STATE_ON_TIME = (REASON_TIME << 4) + DO_REPORT_STATE,
	DECISION_REPORT_STATE_WHEN_CHANGING = (REASON_CHANGE << 4) + DO_REPORT_STATE
};

typedef struct decisions
{
	decision
		turn_lamp_switch,
		turn_pump_switch,
		send_report;
} decisions_t;
