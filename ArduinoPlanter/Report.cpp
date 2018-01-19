
#include "Report.h"

void Report::setReadings(readings_t * readings)
{
	contents["time"] = readings->time;
	contents["acidity"] = readings->acidity;
	contents["waterBottom"] = readings->waterBottom;
	contents["waterTop"] = readings->waterTop;
	contents["lamp"] = readings->isLampOn;
	contents["pump"] = readings->isPumpOn;
}
