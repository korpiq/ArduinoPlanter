#include "ArduinoPlanterSetup.h"

void ArduinoPlanterSetup::init(arduino_planter_configuration_t *configuration)
{
	acidityReader.init(configuration->acidity_pin);
	airReader.init(configuration->air_read_pin);
	waterBottomReader.init(configuration->water_bottom_pin);
	waterTopReader.init(configuration->water_top_pin);
	lampWriter.init(configuration->lamp_pin);
	pumpWriter.init(configuration->pump_pin);
	serialCommunicator.init(configuration->serial_port_speed);

}

void ArduinoPlanterSetup::updateReadings(readings_t *readings)
{
	readings->time = millis();
	readings->acidity = acidityReader.read();
	readings->waterBottom = waterBottomReader.read();
	readings->waterTop = waterTopReader.read();
	readings->communication = serialCommunicator.available();
}
