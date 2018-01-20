#include "ArduinoPlanterSetup.h"

void ArduinoPlanterSetup::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;

	pinMode(configuration.air_read_pin, INPUT);
	pinMode(configuration.water_bottom_pin, INPUT);
	pinMode(configuration.water_top_pin, INPUT);

	pinMode(configuration.lamp_pin, OUTPUT);
	pinMode(configuration.lamp_pin, OUTPUT);

	initSerial(configuration.serial_port_speed);
}

void ArduinoPlanterSetup::initSerial(int baudRate)
{
	// initialize only when not yet started to avoid hanging on begin
	if (!Serial)
	{
		Serial.begin(baudRate);
		while (!Serial); // wait for Serial to initialize
	}
}

void ArduinoPlanterSetup::updateReadings(readings_t & readings)
{
	readings.time = millis();
	readings.acidity = analogRead(configuration->acidity_pin);
	readings.waterBottom = readWaterSensor(configuration->water_bottom_pin);
	readings.waterTop = readWaterSensor(configuration->water_top_pin);
	readings.isLampOn = isLampOn;
	readings.isPumpOn = isPumpOn;
	readings.communication = Serial.available();
}

bool ArduinoPlanterSetup::readWaterSensor(digital_in_t pin)
{
	return digitalRead(pin) == configuration->water_sensor_value_when_wet;
}

void ArduinoPlanterSetup::setLamp(bool on)
{
	digitalWrite(configuration->lamp_pin, (isLampOn = on) ? HIGH : LOW);
}

void ArduinoPlanterSetup::setPump(bool on)
{
	digitalWrite(configuration->pump_pin, (isPumpOn = on) ? HIGH : LOW);
}
