
#include "Configuration.h"

const char PROGMEM confname_acidity_pin[] = "acidity_pin";
const char PROGMEM confname_air_read_pin[] = "air_read_pin";
const char PROGMEM confname_water_bottom_pin[] = "water_bottom_pin";
const char PROGMEM confname_water_top_pin[] = "water_top_pin";
const char PROGMEM confname_lamp_pin[] = "lamp_pin";
const char PROGMEM confname_pump_pin[] = "pump_pin";
const char PROGMEM confname_lamp_cycle_time[] = "lamp_cycle_time";
const char PROGMEM confname_lamp_active_time[] = "lamp_active_time";
const char PROGMEM confname_pump_cycle_time[] = "pump_cycle_time";
const char PROGMEM confname_pump_active_time[] = "pump_active_time";
const char PROGMEM confname_air_read_interval[] = "air_read_interval";
const char PROGMEM confname_report_interval[] = "report_interval";
const char PROGMEM confname_remote_control_timeout[] = "remote_control_timeout";
const char PROGMEM confname_startup_delay[] = "startup_delay";
const char PROGMEM confname_serial_port_speed[] = "serial_port_speed";
const char PROGMEM confname_water_sensor_value_when_wet[] = "water_sensor_value_when_wet";
const char PROGMEM confname_air_sensor_type[] = "air_sensor_type";

const char * const PROGMEM configuration_setting_names[NUMBER_OF_CONFIGURATION_SETTINGS] =
{
	confname_acidity_pin,
	confname_air_read_pin,
	confname_water_bottom_pin,
	confname_water_top_pin,
	confname_lamp_pin,
	confname_pump_pin,
	confname_lamp_cycle_time,
	confname_lamp_active_time,
	confname_pump_cycle_time,
	confname_pump_active_time,
	confname_air_read_interval,
	confname_report_interval,
	confname_remote_control_timeout,
	confname_startup_delay,
	confname_serial_port_speed,
	confname_water_sensor_value_when_wet,
	confname_air_sensor_type
};
