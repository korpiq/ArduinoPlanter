#include "ArduinoPlanterSetup.h"

void ArduinoPlanterSetup::init(arduino_planter_configuration_t & configuration)
{
	this->configuration = &configuration;
	initDevice(configuration);
}

void ArduinoPlanterSetup::initDevice(arduino_planter_configuration_t & configuration)
{
	pinMode(configuration.air_read_pin, INPUT);
	pinMode(configuration.water_bottom_pin, INPUT);
	pinMode(configuration.water_top_pin, INPUT);

	pinMode(configuration.lamp_pin, OUTPUT);
	pinMode(configuration.pump_pin, OUTPUT);

	airSensor = new DHT(configuration.air_read_pin, configuration.air_sensor_type);
	airSensor->begin();
}

void ArduinoPlanterSetup::initState(planter_state_t & state)
{
	this->state = &state;
	state.lamp_start_time = configuration->startup_delay - configuration->lamp_cycle_time;
	state.lamp_stop_time = 0;
	state.pump_start_time = configuration->startup_delay - configuration->pump_cycle_time;
	state.pump_stop_time = 0;
	state.air_read_time = configuration->startup_delay - configuration->air_read_interval;
	state.report_sent_time = -configuration->report_interval;
	state.input_result = SILENT;
}

void ArduinoPlanterSetup::updateReadings()
{
	readings_t & readings = state->readings;

	readings.time = millis();
	readings.acidity = analogRead(configuration->acidity_pin);

	readings.waterOnBottom = readWaterSensor(configuration->water_bottom_pin);
	readings.waterOnTop = readWaterSensor(configuration->water_top_pin);
	readings.waterLevelOk = readings.waterOnBottom && !readings.waterOnTop;

	readings.isLampOn = isLampOn;
	readings.isPumpOn = isPumpOn;
	readings.communication = Serial.available();

	if ((readings.time - state->air_read_time) >= configuration->air_read_interval) {
		readings.humidity = airSensor->readHumidity();
		readings.temperature = airSensor->readTemperature();

		int measure = analogRead(configuration->acidity_pin);
		double voltage = 5 / 1024.0 * measure; // classic digital to voltage conversion
		readings.acidity = 7 + ((2.5 - voltage) / 0.18); // 0-5V to PH range

		state->air_read_time = readings.time;
	}
}

bool ArduinoPlanterSetup::readWaterSensor(digital_in_t pin)
{
	return digitalRead(pin) == configuration->water_sensor_value_when_wet;
}

void ArduinoPlanterSetup::setLamp(bool on)
{
	digitalWrite(configuration->lamp_pin, (isLampOn = on) ? HIGH : LOW);
	*(on ? &state->lamp_start_time : &state->lamp_stop_time) = millis();
}

void ArduinoPlanterSetup::setPump(bool on)
{
	if (state->readings.waterLevelOk || !on)
	{
		digitalWrite(configuration->pump_pin, (isPumpOn = on) ? HIGH : LOW);
		*(on ? &state->pump_start_time : &state->pump_stop_time) = millis();
	}
}
