#ifndef ARDUINO_PLANTER_CONFIGURATION
#define ARDUINO_PLANTER_CONFIGURATION

#include "arduino_planter_types.h"

// buffers are reserved on stack, sometimes on top of each other
#define INPUT_BUFSIZ 300
#define JSON_BUFSIZ  300

/* Declaration of available planter configuration settings */

typedef struct arduino_planter_configuration {
	analog_in_t
		acidity_pin; // PH

	digital_in_t
		air_read_pin, // temperature and humidity
		water_bottom_pin, // dry when out of water
		water_top_pin; // wet when planter is full of water

	digital_out_t
		lamp_pin,
		pump_pin;

	milliseconds_t
		lamp_cycle_time,
		lamp_active_time,

		pump_cycle_time,
		pump_active_time,

		air_read_interval,
		report_interval,
		communication_timeout,
		startup_delay;

	long
		serial_port_speed;
	int
		water_sensor_value_when_wet,
		air_sensor_type;
} arduino_planter_configuration_t;

extern arduino_planter_configuration_t default_configuration;

#endif
