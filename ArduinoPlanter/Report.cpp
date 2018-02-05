
#include "Report.h"

void Report::sendReadings(readings_t * readings)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	contents["time"] = readings->time;
	contents["acidity"] = readings->acidity;
	contents["humidity"] = readings->humidity;
	contents["temperature"] = readings->temperature;
	contents["water_on_bottom"] = readings->water_on_bottom;
	contents["water_on_top"] = readings->water_on_top;
	contents["lamp"] = readings->is_lamp_on;
	contents["pump"] = readings->is_pump_on;
	contents["remote_control"] = readings->is_remote_control;

	send(contents);
}

void Report::sendDecisions(const decisions_t * const decisions)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	if (decisions->turn_lamp_switch)
	{
		contents["lamp_action"] = action_names[decisions->turn_lamp_switch & 15];
		contents["lamp_reason"] = reason_descriptions[decisions->turn_lamp_switch >> 4];
	}

	if (decisions->turn_pump_switch)
	{
		contents["pump_action"] = action_names[decisions->turn_pump_switch & 15];
		contents["pump_reason"] = reason_descriptions[decisions->turn_pump_switch >> 4];
	}

	if (decisions->report_state)
	{
		contents["state_action"] = action_names[decisions->report_state & 15];
		contents["state_reason"] = reason_descriptions[decisions->report_state >> 4];
	}

	if (decisions->report_configuration)
	{
		contents["configuration_action"] = action_names[decisions->report_configuration & 15];
		contents["configuration_reason"] = reason_descriptions[decisions->report_configuration >> 4];
	}

	send(contents);
}

void Report::sendState(planter_state_t * state)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	contents["lamp_started"] = state->lamp_start_time;
	contents["lamp_stopped"] = state->lamp_stop_time;
	contents["pump_started"] = state->pump_start_time;
	contents["pump_stopped"] = state->pump_stop_time;
	contents["air_read"] = state->air_read_time;

	send(contents);
}

#define CONFKEY_SIZE 30
void print_conf_key(int id)
{
	char buffer[CONFKEY_SIZE + 1];
	strncpy_P(buffer, (const char *)pgm_read_word(&(configuration_setting_names[id])), CONFKEY_SIZE);
	buffer[CONFKEY_SIZE] = 0;

	Serial.print('"');
	Serial.print(buffer);
	Serial.print('"');
	Serial.print(':');
}

void print_conf_field(int id, uint32_t value, char separator)
{
	print_conf_key(id);
	Serial.print(value);
	Serial.print(separator);
}

void Report::sendConfiguration(arduino_planter_configuration_t * configuration)
{
	Serial.print('{');
	print_conf_field(CONF_ACIDITY_PIN, configuration->acidity_pin, ',');
	print_conf_field(CONF_AIR_READ_PIN, configuration->air_read_pin, ',');
	print_conf_field(CONF_WATER_BOTTOM_PIN, configuration->water_bottom_pin, ',');
	print_conf_field(CONF_WATER_TOP_PIN, configuration->water_top_pin, ',');
	print_conf_field(CONF_LAMP_PIN, configuration->lamp_pin, ',');
	print_conf_field(CONF_PUMP_PIN, configuration->pump_pin, ',');
	print_conf_field(CONF_LAMP_CYCLE_TIME, configuration->lamp_cycle_time, ',');
	print_conf_field(CONF_LAMP_ACTIVE_TIME, configuration->lamp_active_time, ',');
	print_conf_field(CONF_PUMP_CYCLE_TIME, configuration->pump_cycle_time, ',');
	print_conf_field(CONF_PUMP_ACTIVE_TIME, configuration->pump_active_time, ',');
	print_conf_field(CONF_AIR_READ_INTERVAL, configuration->air_read_interval, ',');
	print_conf_field(CONF_REPORT_INTERVAL, configuration->report_interval, ',');
	print_conf_field(CONF_REMOTE_CONTROL_TIMEOUT, configuration->remote_control_timeout, ',');
	print_conf_field(CONF_STARTUP_DELAY, configuration->startup_delay, ',');
	print_conf_field(CONF_SERIAL_PORT_SPEED, configuration->serial_port_speed, ',');
	print_conf_field(CONF_WATER_SENSOR_VALUE_WHEN_WET, configuration->water_sensor_value_when_wet, ',');
	print_conf_field(CONF_AIR_SENSOR_TYPE, configuration->air_sensor_type, '}');
	Serial.println();
	Serial.flush();
}

void Report::send(JsonObject & contents)
{
	contents.printTo(Serial);
	Serial.write("\r\n");
	Serial.flush();
}
