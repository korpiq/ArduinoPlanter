
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

void Report::sendConfiguration(arduino_planter_configuration_t * configuration)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	contents["acidity_pin"] = configuration->acidity_pin;
	contents["air_read_pin"] = configuration->air_read_pin;
	contents["water_bottom_pin"] = configuration->water_bottom_pin;
	contents["water_top_pin"] = configuration->water_top_pin;
	contents["lamp_pin"] = configuration->lamp_pin;
	contents["pump_pin"] = configuration->pump_pin;
	contents["lamp_cycle_time"] = configuration->lamp_cycle_time;
	contents["lamp_active_time"] = configuration->lamp_active_time;
	contents["pump_cycle_time"] = configuration->pump_cycle_time;
	contents["pump_active_time"] = configuration->pump_active_time;
	contents["air_read_interval"] = configuration->air_read_interval;
	contents["report_interval"] = configuration->report_interval;
	contents["remote_control_timeout"] = configuration->remote_control_timeout;
	contents["startup_delay"] = configuration->startup_delay;
	contents["serial_port_speed"] = configuration->serial_port_speed;
	contents["water_sensor_value_when_wet"] = configuration->water_sensor_value_when_wet;
	contents["air_sensor_type"] = configuration->air_sensor_type;

	send(contents);
}

void Report::send(JsonObject & contents)
{
	contents.printTo(Serial);
	Serial.write("\r\n");
	Serial.flush();
}
