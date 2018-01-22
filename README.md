# ArduinoPlanter

Arduino program for growing plants automatically in a planter.

## Prerequisites

Arduino libraries:

 - Adafruit DHT
    - Adafruit Unified Sensor (1.0.2)

## Configuration

Configuration.c contains the settings:
 - which port is connected to which device
 - timings of operations such as watering and showing light for the plants.

Define _DEBUG to use debug instead of production configuration.
