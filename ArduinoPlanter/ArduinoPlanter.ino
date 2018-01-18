/*
 Name:		ArduinoPlanter.ino
 Created:	1/17/2018 10:14:21 PM
 Author:	Kalle Hallivuori <korpiq@iki.fi>
*/

#include "Report.h"
#include "arduino_planter_types.h"
#include "Configuration.h"
#include "ArduinoPlanterSetup.h"
#include "Readings.h"

ArduinoPlanterSetup planterSetup;
Report report;
readings_t readings;

// the setup function runs once when you press reset or power the board
void setup() {
	planterSetup.init(&default_configuration);
}

// the loop function runs over and over again until power down or reset
void loop() {
	planterSetup.updateReadings(&readings);

	report.setReadings(&readings);
	planterSetup.serialCommunicator.write(&report.contents);
}
