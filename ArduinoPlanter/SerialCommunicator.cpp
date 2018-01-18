// 
// 
// 

#include "SerialCommunicator.h"

void SerialCommunicator::init(int baudRate)
{
	Serial.begin(baudRate);
	while (!Serial); // wait for Serial to initialize
}

bool SerialCommunicator::available()
{
	return Serial.available();
}

int SerialCommunicator::read()
{
	return Serial.read();
}

void SerialCommunicator::write(JsonObject &json)
{
	json.printTo(Serial);
}
