// Setup.h

#ifndef _ARDUINO_PLANTER_SETUP_h
#define _ARDUINO_PLANTER_SETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "Readings.h"

class ArduinoPlanterSetup
{
private:
	arduino_planter_configuration_t * configuration;
	bool isLampOn = false, isPumpOn = false;
	void initSerial(int baudRate);

public:
	void init(arduino_planter_configuration_t&);
	void updateReadings(readings_t&);
	void setLamp(bool on);
	void setPump(bool on);
};

#endif

