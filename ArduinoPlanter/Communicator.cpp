
#include "Communicator.h"
#include "ArduinoJson.h"

void Communicator::init(arduino_planter_configuration_t & configuration, planter_state_t & state)
{
	this->configuration = &configuration;
	this->state = &state;
}

void Communicator::listen()
{
	state->input_result = Serial.available() ? receive() : SILENT;
}

input_result Communicator::receive()
{
	char buffer[INPUT_BUFSIZ];
	size_t bytecount = Serial.readBytesUntil('\n', buffer, INPUT_BUFSIZ - 1);
	return bytecount ? handleInput(buffer) : SILENT;
}

input_result Communicator::handleInput(char const * buffer)
{
	switch (*buffer)
	{
		case 'p': return PUMP;
		case 'l': return LAMP;
		case 'c': return REPORT_CONFIGURATION;
		case 's': return REPORT_STATE;
		case 'o': return ONLINE_MODE;
		case '{':
			if (buffer[1]) // avoid hanging parser with sole '{'
				return handleJson(buffer);
		case '\r':
		case '\n': return SILENT;
		default:
			return INVALID;
	}
}

input_result Communicator::handleJson(char const * buffer)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject &input = jsonBuffer.parseObject(buffer);

	if (&input == &JsonObject::invalid())
	{
		return INVALID;
	}

	input_result_t result = SILENT;

	for (JsonObject::iterator it = input.begin(); it != input.end(); ++it)
	{
		if (!strcmp("acidity_pin", it->key))
		{
			configuration->acidity_pin = (analog_in_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("air_read_pin", it->key))
		{
			configuration->air_read_pin = (digital_in_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("water_bottom_pin", it->key))
		{
			configuration->water_bottom_pin = (digital_in_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("water_top_pin", it->key))
		{
			configuration->water_top_pin = (digital_in_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("lamp_pin", it->key))
		{
			configuration->lamp_pin = (digital_out_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("pump_pin", it->key))
		{
			configuration->pump_pin = (digital_out_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("lamp_cycle_time", it->key))
		{
			configuration->lamp_cycle_time = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("lamp_active_time", it->key))
		{
			configuration->lamp_active_time = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("pump_cycle_time", it->key))
		{
			configuration->pump_cycle_time = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("pump_active_time", it->key))
		{
			configuration->pump_active_time = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("air_read_interval", it->key))
		{
			configuration->air_read_interval = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("report_interval", it->key))
		{
			configuration->report_interval = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("communication_timeout", it->key))
		{
			configuration->communication_timeout = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("startup_delay", it->key))
		{
			configuration->startup_delay = (milliseconds_t)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("serial_port_speed", it->key))
		{
			Serial.println("Serial port may not be reconfigured.");
			result = INVALID;
		}
		else if (!strcmp("water_sensor_value_when_wet", it->key))
		{
			configuration->water_sensor_value_when_wet = (int)it->value;
			result = RECONFIGURED;
		}
		else if (!strcmp("air_sensor_type", it->key))
		{
			configuration->air_sensor_type = (int)it->value;
			result = RECONFIGURED;
		}
		else
		{
			Serial.println("Unknown key in JSON input");
			if (result == SILENT)
			{
				return INVALID;
			}
		}
	}

	return result;
}
