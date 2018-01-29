#include "Decisions.h"

const char * const action_nothing = "inaction";
const char * const action_on = "turn on";
const char * const action_off = "turn off";
const char * const action_send = "send report";

const char * const action_names[NUMBER_OF_ACTIONS] =
{
	action_nothing,
	action_on,
	action_off,
	action_send
};

const char * const reason_ok = "Ok";
const char * const reason_request = "Request";
const char * const reason_time = "Time";
const char * const reason_low = "Water low";
const char * const reason_high = "Water high";
const char * const reason_change = "Change";

const char * const reason_descriptions[NUMBER_OF_REASONS] =
{
	reason_ok,
	reason_request,
	reason_time,
	reason_low,
	reason_high,
	reason_change
};
