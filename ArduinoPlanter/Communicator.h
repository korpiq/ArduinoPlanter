// Communicator.h

#ifndef _COMMUNICATOR_h
#define _COMMUNICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Configuration.h"
#include "State.h"

class Communicator
{
private:
	arduino_planter_configuration_t * configuration;
	planter_state_t * state;

	input_result receive();
	input_result handleInput(char const *);
	input_result handleJson(char const *);

public:
	void init(arduino_planter_configuration_t & configuration, planter_state_t & state);
	void listen();
};

#endif

