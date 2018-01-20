// Setup.h

#ifndef _ARDUINO_PLANTER_SETUP_h
#define _ARDUINO_PLANTER_SETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "State.h"

class ArduinoPlanterSetup
{
private:
	arduino_planter_configuration_t * configuration;
	planter_state_t * state;
	bool isLampOn = false, isPumpOn = false;
	void initDevice(arduino_planter_configuration_t&);
	void initState(planter_state_t&);
	void initSerial(int baudRate);
	bool readWaterSensor(digital_in_t pin);

public:
	void init(arduino_planter_configuration_t&, planter_state_t&);
	void updateReadings();
	void setLamp(bool on);
	void setPump(bool on);
};

#endif

