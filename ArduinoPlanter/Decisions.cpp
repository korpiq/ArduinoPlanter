#include "Decisions.h"

const char * const action_nothing PROGMEM = "inaction";
const char * const action_on PROGMEM = "turn on";
const char * const action_off PROGMEM = "turn off";
const char * const action_state PROGMEM = "report state";
const char * const action_conf PROGMEM = "report configuration";

const char * const action_names[NUMBER_OF_ACTIONS] PROGMEM =
{
	action_nothing,
	action_on,
	action_off,
	action_state,
	action_conf
};

const char * const reason_ok PROGMEM = "Ok";
const char * const reason_request PROGMEM = "Request";
const char * const reason_time PROGMEM = "Time";
const char * const reason_low PROGMEM = "Water low";
const char * const reason_high PROGMEM = "Water high";
const char * const reason_change PROGMEM = "Change";

const char * const reason_descriptions[NUMBER_OF_REASONS] PROGMEM =
{
	reason_ok,
	reason_request,
	reason_time,
	reason_low,
	reason_high,
	reason_change
};
