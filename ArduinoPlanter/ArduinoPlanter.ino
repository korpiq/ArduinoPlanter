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
#include "Decider.h"
#include "Report.h"

ArduinoPlanterSetup planterSetup;
planter_state_t state;
Decider decider;
decisions_t decisions;
Report report;

// the setup function runs once when you press reset or power the board
void setup() {
	planterSetup.init(default_configuration, state);
	decider.init(default_configuration);
}

// the loop function runs over and over again until power down or reset
void loop() {
	planterSetup.updateReadings();

	decider.updateDecisions(state, decisions);

	execute_decisions(&decisions);

	delay(100);
}

void execute_decisions(decisions_t * decisions)
{
	bool send_report = decisions->send_report.doThis;

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

	if (send_report)
	{
		report.setReadings(&state.readings);
		report.setState(&state);
		report.setDecisions(decisions);
		report.send();
		state.report_sent_time = state.readings.time;
	}
}
