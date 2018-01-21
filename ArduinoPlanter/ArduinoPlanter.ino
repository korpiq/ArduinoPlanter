/*
 Name:		ArduinoPlanter.ino
 Created:	1/17/2018 10:14:21 PM
 Author:	Kalle Hallivuori <korpiq@iki.fi>
*/

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
	report.setReadings(&state.readings);

	decider.updateDecisions(state, decisions);
	report.setDecisions(&decisions);

	execute_decisions(&decisions);

	report.send();
	delay(1000);
}

void execute_decisions(decisions_t * decisions)
{
	if (decisions->turn_lamp_switch.doThis)
	{
		planterSetup.setLamp(decisions->turn_lamp_switch.doThis == turn_on);
	}

	if (decisions->turn_pump_switch.doThis)
	{
		planterSetup.setPump(decisions->turn_pump_switch.doThis == turn_on);
	}
}
