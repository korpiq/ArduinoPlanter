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
	if (Serial.availableForWrite())
	{
		Serial.println("ArduinoPlanter started.");
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	communicator.listen();

	if (state.input_result == RECONFIGURED)
	{
		Serial.println("Reconfiguring...");
		planterSetup.init(default_configuration);
		Serial.println("Reconfigured.");
	}
	else if (state.input_result == INVALID)
	{
		Serial.println("Invalid input.");
	}

	planterSetup.updateReadings();
	decider.updateDecisions(state, decisions);
	execute_decisions(&decisions);

	delay(100);
}

void execute_decisions(const decisions_t * const decisions)
{
	decision send_report = decisions->send_report;

	switch(decisions->turn_lamp_switch & 15)
	{
		case DO_TURN_ON:
			planterSetup.setLamp(true);
			send_report = DECISION_REPORT_STATE_WHEN_CHANGING;
			break;
		case DO_TURN_OFF:
			planterSetup.setLamp(false);
			send_report = DECISION_REPORT_STATE_WHEN_CHANGING;
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
			send_report = DECISION_REPORT_STATE_WHEN_CHANGING;
			break;
		case DO_TURN_OFF:
			planterSetup.setPump(false);
			send_report = DECISION_REPORT_STATE_WHEN_CHANGING;
			break;
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for pump: ");
			Serial.println(decisions->turn_pump_switch, 16);
	}

	switch (decisions->send_report & 15)
	{
		case DO_REPORT_CONFIGURATION:
			report.sendConfiguration(&default_configuration);
			break;
		case DO_REPORT_STATE: // handled through send_report below
		case DO_NOTHING:
			break;
		default:
			Serial.print("Invalid decision for report: ");
			Serial.println(decisions->send_report, 16);
	}

	switch (send_report & 15)
	{
		case DO_REPORT_CONFIGURATION: // handled above
		case DO_NOTHING:
			break;
		case DO_REPORT_STATE: // handled through send_report below
			report.sendReadings(&state.readings);
			report.sendDecisions(decisions);
			report.sendState(&state);
			state.report_sent_time = state.readings.time;
			break;
		default:
			Serial.print("Invalid decision for report: ");
			Serial.println(send_report, 16);
	}
}
