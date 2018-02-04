/*
 Name:		ArduinoPlanter.ino
 Created:	1/17/2018 10:14:21 PM
 Author:	Kalle Hallivuori <korpiq@iki.fi>
*/

#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>

#include "Configuration.h"
#include "State.h"
#include "ArduinoPlanterSetup.h"
#include "Communicator.h"
#include "Decider.h"
#include "Report.h"

ArduinoPlanterSetup planterSetup;
Communicator communicator;
planter_state_t state;
Decider decider;
decisions_t decisions;
Report report;

// the setup function runs once when you press reset or power the board
void setup() {
	planterSetup.init(default_configuration);
	planterSetup.initState(state);

	decider.init(default_configuration);
	communicator.init(default_configuration, state);

	Serial.begin(default_configuration.serial_port_speed);
}

// the loop function runs over and over again until power down or reset
void loop() {
	communicator.listen();
	handle_input_result(state.input_result);

	planterSetup.updateReadings();
	decider.updateDecisions(state, decisions);
	execute_decisions(&decisions);

	delay(100);
}

void handle_input_result(input_result_t input_result)
{
	switch (input_result)
	{
	case REQUEST_RECONFIGURE:
		planterSetup.init(default_configuration);
		break;
	case REQUEST_CONTROL_REMOTE:
		state.online_mode_time = state.readings.time;
		break;
	case REQUEST_CONTROL_AUTONOMOUS:
		state.online_mode_time = state.readings.time - default_configuration.communication_timeout;
		break;
	case REQUEST_INVALID:
		Serial.println("Invalid input.");
	default:
		break;
	}
}

void execute_decisions(const decisions_t * const decisions)
{
	decision report_state = decisions->report_state;

	switch(decisions->turn_lamp_switch & 15)
	{
		case DO_TURN_ON:
			planterSetup.setLamp(true);
			report_state = DECISION_REPORT_WHEN_CHANGING;
			break;
		case DO_TURN_OFF:
			planterSetup.setLamp(false);
			report_state = DECISION_REPORT_WHEN_CHANGING;
			break;
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for lamp: ");
			Serial.println(decisions->turn_lamp_switch, 16);
	}

	switch (decisions->turn_pump_switch & 15)
	{
		case DO_TURN_ON:
			planterSetup.setPump(true);
			report_state = DECISION_REPORT_WHEN_CHANGING;
			break;
		case DO_TURN_OFF:
			planterSetup.setPump(false);
			report_state = DECISION_REPORT_WHEN_CHANGING;
			break;
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for pump: ");
			Serial.println(decisions->turn_pump_switch, 16);
	}

	switch (decisions->report_configuration & 15)
	{
		case DO_SEND_REPORT:
			report.sendConfiguration(&default_configuration);
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for configuration report: ");
			Serial.println(decisions->report_configuration, 16);
	}

	switch (report_state & 15)
	{
		case DO_SEND_REPORT:
			report.sendReadings(&state.readings);
			report.sendDecisions(decisions);
			report.sendState(&state);
			state.report_sent_time = state.readings.time;
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for report: ");
			Serial.println(report_state, 16);
	}
}
