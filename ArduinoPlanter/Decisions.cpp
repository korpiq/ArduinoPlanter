#include "Decisions.h"

const char PROGMEM action_nothing[] = "inaction";
const char PROGMEM action_on[] = "turn on";
const char PROGMEM action_off[] = "turn off";
const char PROGMEM action_send[] = "send report";

const char * const PROGMEM action_names[NUMBER_OF_ACTIONS] =
{
	action_nothing,
	action_on,
	action_off,
	action_send
};

const char PROGMEM reason_doing_fine[] = "ok";
const char PROGMEM reason_request[] = "request";
const char PROGMEM reason_remote_control_mode[] = "waiting for command";
const char PROGMEM reason_time[] = "time";
const char PROGMEM reason_low[] = "water low";
const char PROGMEM reason_high[] = "water high";
const char PROGMEM reason_change[] = "change";

const char * const PROGMEM reason_descriptions[NUMBER_OF_REASONS] =
{
	reason_doing_fine,
	reason_request,
	reason_remote_control_mode,
	reason_time,
	reason_low,
	reason_high,
	reason_change
};
