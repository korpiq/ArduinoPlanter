#include "Configuration.h"

/* Values for planter configuration settings */

#ifdef VM_DEBUG
#define _DEBUG
#endif

#ifndef _DEBUG

arduino_planter_configuration_t default_configuration = { // PRODUCTION configuration
	.acidity_pin = 0,

	.air_read_pin = 4,
	.water_bottom_pin = 5,
	.water_top_pin = 6,

	.lamp_pin = 2,
	.pump_pin = 3,

	.lamp_cycle_time = 86400000ul, // every 24 hours
	.lamp_delay_time = 5000ul, // activate after 5 seconds
	.lamp_active_time = 57600000ul, // show light for 16 hours

	.pump_cycle_time = 21600000ul, // every 6 hours
	.pump_delay_time = 5000ul, // activate after 5 seconds
	.pump_active_time = 600000ul, // run for 10 minutes at most

	.air_read_interval = 2000ul, // every 2 seconds
	.report_interval = 60000ul, // every 1 minute
	.communication_timeout = 3600000ul, // 1 hour

	.serial_port_speed = 115200l,
	.water_sensor_value_when_wet = 1,
	.air_sensor_type = 22
};

#else

arduino_planter_configuration_t default_configuration = { // DEBUG configuration
	.acidity_pin = 0,

	.air_read_pin = 4,
	.water_bottom_pin = 5,
	.water_top_pin = 6,

	.lamp_pin = 2,
	.pump_pin = 3,

	.lamp_cycle_time = 12000ul, // 12 second "day"
	.lamp_delay_time = 2000ul,
	.lamp_active_time = 8000ul,

	.pump_cycle_time = 4000ul, // 4 second watering cycle
	.pump_delay_time = 3000ul,
	.pump_active_time = 1000ul,

	.air_read_interval = 5000ul, // every 5 seconds
	.report_interval = 5000ul, // every 5 seconds
	.communication_timeout = 3600000ul, // 1 hour

	.serial_port_speed = 115200l,
	.water_sensor_value_when_wet = 1,
	.air_sensor_type = 22
};

#endif
