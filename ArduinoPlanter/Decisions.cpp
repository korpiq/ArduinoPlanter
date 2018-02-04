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

const char * const reason_doing_fine = "ok";
const char * const reason_request = "request";
const char * const reason_remote_control_mode = "waiting for command";
const char * const reason_time = "time";
const char * const reason_low = "water low";
const char * const reason_high = "water high";
const char * const reason_change = "change";

const char * const reason_descriptions[NUMBER_OF_REASONS] =
{
	reason_doing_fine,
	reason_request,
	reason_remote_control_mode,
	reason_time,
	reason_low,
	reason_high,
	reason_change
};
