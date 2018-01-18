/*
 Name:		ArduinoPlanter.ino
 Created:	1/17/2018 10:14:21 PM
 Author:	Kalle Hallivuori <korpiq@iki.fi>
*/

#include "arduino_planter_types.h"
#include "arduino_planter_types_h.h"
#include "Configuration.h"
#include "ArduinoPlanterSetup.h"

ArduinoPlanterSetup * planterSetup = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
	planterSetup = new ArduinoPlanterSetup(&default_configuration);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
