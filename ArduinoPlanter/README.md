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

Define VM_DEBUG to use debug instead of production configuration.

### Live Reconfiguring

Send a JSON object over Serial line (USB) to change configuration settings.
Keys equal to field names in Configuration set respective values.
Unrecognized keys will be ignored with a warning.

## Communicating

Send commands over serial line (USB):

 - 'c': report configuration.
 - 's': report status.
 - 'p': switch pump state (on <-> off).
 - 'l': switch lamp state (on <-> off).
 - 'r': remote control mode: turn devices on or off by timer until communication_timeout has passed.
 - 'a': autonomous control mode: turn devices on and off by timer.
