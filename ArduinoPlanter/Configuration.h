#ifndef ARDUINO_PLANTER_CONFIGURATION
#define ARDUINO_PLANTER_CONFIGURATION

#include "arduino_planter_types.h"
#include "avr/pgmspace.h"

// buffers are reserved on stack, sometimes on top of each other
#define INPUT_BUFSIZ 280
#define JSON_BUFSIZ  300

/* Declaration of available planter configuration settings */

enum configuration_settings {
	CONF_ACIDITY_PIN,
	CONF_AIR_READ_PIN,
	CONF_WATER_BOTTOM_PIN,
	CONF_WATER_TOP_PIN,
	CONF_LAMP_PIN,
	CONF_PUMP_PIN,
	CONF_LAMP_CYCLE_TIME,
	CONF_LAMP_ACTIVE_TIME,
	CONF_PUMP_CYCLE_TIME,
	CONF_PUMP_ACTIVE_TIME,
	CONF_AIR_READ_INTERVAL,
	CONF_REPORT_INTERVAL,
	CONF_REMOTE_CONTROL_TIMEOUT,
	CONF_STARTUP_DELAY,
	CONF_SERIAL_PORT_SPEED,
	CONF_WATER_SENSOR_VALUE_WHEN_WET,
	CONF_AIR_SENSOR_TYPE,
	NUMBER_OF_CONFIGURATION_SETTINGS
};

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
		remote_control_timeout,
		startup_delay;

	long
		serial_port_speed;
	int
		water_sensor_value_when_wet,
		air_sensor_type;
} arduino_planter_configuration_t;

extern arduino_planter_configuration_t default_configuration;
extern const char * const configuration_setting_names[NUMBER_OF_CONFIGURATION_SETTINGS] PROGMEM;

#endif
