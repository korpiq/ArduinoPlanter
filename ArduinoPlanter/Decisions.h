#pragma once

typedef struct decision
{
	char const * doThis; // when set, call associated handler with this parameter
	char const * reason;
} decision_t;

typedef struct decisions
{
	decision_t
		turn_lamp_switch,
		turn_pump_switch,
		send_report;
} decisions_t;

extern char const * turn_on;
extern char const * turn_off;
extern char const * do_once;
