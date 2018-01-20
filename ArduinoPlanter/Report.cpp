
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

void Report::send()
{
	contents.printTo(Serial);
	Serial.write("\r\n");
	Serial.flush();
}
