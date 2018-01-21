#include "Configuration.h"

/* Values for planter configuration settings */

arduino_planter_configuration_t default_configuration = {
	.acidity_pin = 0,

	.air_read_pin = 4,
	.water_bottom_pin = 5,
	.water_top_pin = 6,

	.lamp_pin = 2,
	.pump_pin = 3,

	.lamp_cycle_time = 86400000ul, // every 24 hours
	.lamp_delay_time = 28800000ul, // activate after 8 hours
	.lamp_active_time = 57600000ul, // show light for 16 hours

	.pump_cycle_time = 21600000ul, // every 6 hours
	.pump_delay_time = 0ul, // activate at beginning of cycle
	.pump_active_time = 600000ul, // run for 10 minutes

	.air_read_interval = 2000ul, // every 2 seconds
	.report_interval = 2000ul, // every 2 seconds
	.communication_timeout = 3600000ul, // 1 hour

	.serial_port_speed = 115200,
	.water_sensor_value_when_wet = 1
};
