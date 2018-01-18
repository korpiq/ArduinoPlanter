#include "ArduinoPlanterSetup.h"

void ArduinoPlanterSetup::init(arduino_planter_configuration_t *configuration)
{
	acidityReader = new AnalogReader(configuration->acidity_pin);
	airReader = new DigitalReader(configuration->air_read_pin);
	waterBottomReader = new DigitalReader(configuration->water_bottom_pin);
	waterTopReader = new DigitalReader(configuration->water_top_pin);
	lampWriter = new DigitalWriter(configuration->lamp_pin);
	pumpWriter = new DigitalWriter(configuration->pump_pin);
}

void ArduinoPlanterSetup::clear()
{
	delete acidityReader;
	delete airReader;
	delete waterBottomReader;
	delete waterTopReader;
	delete lampWriter;
	delete pumpWriter;
}
