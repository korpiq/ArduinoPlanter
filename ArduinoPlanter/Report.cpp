
#include "Report.h"

void Report::setReadings(readings_t * readings)
{
	JsonObject & contents = * jsonObject;
	contents["time"] = readings->time;
	contents["acidity"] = readings->acidity;
	contents["humidity"] = readings->humidity;
	contents["temperature"] = readings->temperature;
	contents["waterOnBottom"] = readings->waterOnBottom;
	contents["waterOnTop"] = readings->waterOnTop;
	contents["lamp"] = readings->isLampOn;
	contents["pump"] = readings->isPumpOn;
}

void Report::setDecisions(decisions_t * decisions)
{
	JsonObject & contents = *jsonObject;
	contents["lamp_decision"] = decisions->turn_lamp_switch.doThis;
	contents["lamp_reason"] = decisions->turn_lamp_switch.reason;
	contents["pump_decision"] = decisions->turn_pump_switch.doThis;
	contents["pump_reason"] = decisions->turn_pump_switch.reason;
}

void Report::setState(planter_state_t * state)
{
	JsonObject & contents = *jsonObject;
	contents["lamp_started"] = state->lamp_start_time;
	contents["lamp_stopped"] = state->lamp_stop_time;
	contents["pump_started"] = state->pump_start_time;
	contents["pump_stopped"] = state->pump_stop_time;
	contents["air_read"] = state->air_read_time;
}

void Report::send()
{
	JsonObject & contents = *jsonObject;
	contents.printTo(Serial);
	Serial.write("\r\n");
	Serial.flush();
}
