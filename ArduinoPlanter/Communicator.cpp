
#include "Communicator.h"
#include "ArduinoJson.h"
#include "Configuration.h"

void Communicator::init(arduino_planter_configuration_t & configuration, planter_state_t & state)
{
	this->configuration = &configuration;
	this->state = &state;
}

void Communicator::listen()
{
	state->input_result = Serial.available() ? receive() : REQUEST_NOTHING;
}

input_result Communicator::receive()
{
	char buffer[INPUT_BUFSIZ];
	size_t bytecount = Serial.readBytesUntil('\n', buffer, INPUT_BUFSIZ - 1);
	return bytecount ? handleInput(buffer) : REQUEST_NOTHING;
}

input_result Communicator::handleInput(char const * buffer)
{
	switch (*buffer)
	{
		case 'p': return REQUEST_PUMP;
		case 'l': return REQUEST_LAMP;
		case 'c': return REQUEST_REPORT_CONFIGURATION;
		case 's': return REQUEST_REPORT_STATE;
		case 'r': return REQUEST_CONTROL_REMOTE;
		case 'a': return REQUEST_CONTROL_AUTONOMOUS;
		case '{':
			if (buffer[1]) // avoid hanging parser with sole '{'
				return handleJson(buffer);
		case '\r':
		case '\n': return REQUEST_NOTHING;
		default:
			return REQUEST_INVALID;
	}
}

bool is_conf_key(int id, const char * key)
{
	return !strcmp_P(key, (const char *)pgm_read_word(&(configuration_setting_names[id])));
}

input_result Communicator::handleJson(char const * buffer)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject &input = jsonBuffer.parseObject(buffer);

	if (&input == &JsonObject::invalid())
	{
		return REQUEST_INVALID;
	}

	input_result_t result = REQUEST_NOTHING;

	for (JsonObject::iterator it = input.begin(); it != input.end(); ++it)
	{
		if (is_conf_key(CONF_ACIDITY_PIN, it->key))
		{
			configuration->acidity_pin = (analog_in_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_AIR_READ_PIN, it->key))
		{
			configuration->air_read_pin = (digital_in_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_WATER_BOTTOM_PIN, it->key))
		{
			configuration->water_bottom_pin = (digital_in_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_WATER_TOP_PIN, it->key))
		{
			configuration->water_top_pin = (digital_in_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_LAMP_PIN, it->key))
		{
			configuration->lamp_pin = (digital_out_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_PUMP_PIN, it->key))
		{
			configuration->pump_pin = (digital_out_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_LAMP_CYCLE_TIME, it->key))
		{
			configuration->lamp_cycle_time = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_LAMP_ACTIVE_TIME, it->key))
		{
			configuration->lamp_active_time = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_PUMP_CYCLE_TIME, it->key))
		{
			configuration->pump_cycle_time = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_PUMP_ACTIVE_TIME, it->key))
		{
			configuration->pump_active_time = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_AIR_READ_INTERVAL, it->key))
		{
			configuration->air_read_interval = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_REPORT_INTERVAL, it->key))
		{
			configuration->report_interval = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_REMOTE_CONTROL_TIMEOUT, it->key))
		{
			configuration->remote_control_timeout = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_STARTUP_DELAY, it->key))
		{
			configuration->startup_delay = (milliseconds_t)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_SERIAL_PORT_SPEED, it->key))
		{
			Serial.println("Serial port may not be reconfigured.");
			result = REQUEST_INVALID;
		}
		else if (is_conf_key(CONF_WATER_SENSOR_VALUE_WHEN_WET, it->key))
		{
			configuration->water_sensor_value_when_wet = (int)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else if (is_conf_key(CONF_AIR_SENSOR_TYPE, it->key))
		{
			configuration->air_sensor_type = (int)it->value;
			result = REQUEST_RECONFIGURE;
		}
		else
		{
			Serial.println("Unknown key in JSON input");
			if (result == REQUEST_NOTHING)
			{
				return REQUEST_INVALID;
			}
		}
	}

	return result;
}
