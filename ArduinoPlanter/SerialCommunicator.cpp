// 
// 
// 

#include "SerialCommunicator.h"

void SerialCommunicator::init(int baudRate)
{
	if (!Serial)
	{
		// initialize only when not yet started to avoid hanging on begin
		Serial.begin(baudRate);
		while (!Serial); // wait for Serial to initialize
	}
}

bool SerialCommunicator::available()
{
	return Serial.available();
}

int SerialCommunicator::read()
{
	return Serial.read();
}

void SerialCommunicator::write(JsonObject *json)
{
	json->printTo(Serial);
	Serial.write("\r\n");
}
