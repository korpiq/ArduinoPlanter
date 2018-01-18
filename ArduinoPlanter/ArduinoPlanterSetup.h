// Setup.h

#ifndef _ARDUINO_PLANTER_SETUP_h
#define _ARDUINO_PLANTER_SETUP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "AnalogReader.h"
#include "DigitalReader.h"
#include "DigitalWriter.h"
#include "SerialCommunicator.h"
#include "Readings.h"

class ArduinoPlanterSetup
{
private:
	AnalogReader
		acidityReader;

	DigitalReader
		airReader,
		waterBottomReader,
		waterTopReader;

	DigitalWriter
		lampWriter,
		pumpWriter;

	SerialCommunicator
		serialCommunicator;

public:
	void init(arduino_planter_configuration_t*);
	void updateReadings(readings_t*);
};

#endif

