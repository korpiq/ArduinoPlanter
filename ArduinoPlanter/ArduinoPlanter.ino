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

void execute_decisions(decisions_t * decisions)
{
	bool send_report = decisions->send_report.doThis == report_state;

	if (decisions->turn_lamp_switch.doThis)
	{
		planterSetup.setLamp(decisions->turn_lamp_switch.doThis == turn_on);
		send_report = true;
	}

	if (decisions->turn_pump_switch.doThis)
	{
		planterSetup.setPump(decisions->turn_pump_switch.doThis == turn_on);
		send_report = true;
	}

	if (decisions->send_report.doThis == report_configuration)
	{
		report.sendConfiguration(&default_configuration);
	}

	if (send_report)
	{
		report.sendReadings(&state.readings);
		report.sendDecisions(decisions);
		report.sendState(&state);
		state.report_sent_time = state.readings.time;
	}
}
