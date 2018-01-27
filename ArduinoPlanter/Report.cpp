
#include "Report.h"

void Report::sendReadings(readings_t * readings)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	contents["time"] = readings->time;
	contents["acidity"] = readings->acidity;
	contents["humidity"] = readings->humidity;
	contents["temperature"] = readings->temperature;
	contents["waterOnBottom"] = readings->waterOnBottom;
	contents["waterOnTop"] = readings->waterOnTop;
	contents["lamp"] = readings->isLampOn;
	contents["pump"] = readings->isPumpOn;

	send(contents);
}

void Report::sendDecisions(decisions_t * decisions)
{
	StaticJsonBuffer<JSON_BUFSIZ> jsonBuffer;
	JsonObject & contents = jsonBuffer.createObject();

	contents["lamp_decision"] = decisions->turn_lamp_switch.doThis;
	contents["lamp_reason"] = decisions->turn_lamp_switch.reason;
	contents["pump_decision"] = decisions->turn_pump_switch.doThis;
	contents["pump_reason"] = decisions->turn_pump_switch.reason;

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
	contents["lamp_delay_time"] = configuration->lamp_delay_time;
	contents["lamp_active_time"] = configuration->lamp_active_time;
	contents["pump_cycle_time"] = configuration->pump_cycle_time;
	contents["pump_delay_time"] = configuration->pump_delay_time;
	contents["pump_active_time"] = configuration->pump_active_time;
	contents["air_read_interval"] = configuration->air_read_interval;
	contents["report_interval"] = configuration->report_interval;
	contents["communication_timeout"] = configuration->communication_timeout;
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
