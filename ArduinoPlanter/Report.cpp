
#include "Report.h"

void Report::setReadings(readings_t * readings)
{
	contents["time"] = readings->time;
	contents["acidity"] = readings->acidity;
	contents["waterOnBottom"] = readings->waterOnBottom;
	contents["waterOnTop"] = readings->waterOnTop;
	contents["lamp"] = readings->isLampOn;
	contents["pump"] = readings->isPumpOn;
}

void Report::setDecisions(decisions_t * decisions)
{
	contents["lamp_decision"] = decisions->turn_lamp_switch.doThis;
	contents["lamp_reason"] = decisions->turn_lamp_switch.reason;
	contents["pump_decision"] = decisions->turn_pump_switch.doThis;
	contents["pump_reason"] = decisions->turn_pump_switch.reason;
}

void Report::send()
{
	contents.printTo(Serial);
	Serial.write("\r\n");
	Serial.flush();
}
