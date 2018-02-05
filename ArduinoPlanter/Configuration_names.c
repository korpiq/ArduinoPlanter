
#include "Configuration.h"

const char confname_acidity_pin[] PROGMEM = "acidity_pin";
const char confname_air_read_pin[] PROGMEM = "air_read_pin";
const char confname_water_bottom_pin[] PROGMEM = "water_bottom_pin";
const char confname_water_top_pin[] PROGMEM = "water_top_pin";
const char confname_lamp_pin[] PROGMEM = "lamp_pin";
const char confname_pump_pin[] PROGMEM = "pump_pin";
const char confname_lamp_cycle_time[] PROGMEM = "lamp_cycle_time";
const char confname_lamp_active_time[] PROGMEM = "lamp_active_time";
const char confname_pump_cycle_time[] PROGMEM = "pump_cycle_time";
const char confname_pump_active_time[] PROGMEM = "pump_active_time";
const char confname_air_read_interval[] PROGMEM = "air_read_interval";
const char confname_report_interval[] PROGMEM = "report_interval";
const char confname_remote_control_timeout[] PROGMEM = "remote_control_timeout";
const char confname_startup_delay[] PROGMEM = "startup_delay";
const char confname_serial_port_speed[] PROGMEM = "serial_port_speed";
const char confname_water_sensor_value_when_wet[] PROGMEM = "water_sensor_value_when_wet";
const char confname_air_sensor_type[] PROGMEM = "air_sensor_type";

const char * const configuration_setting_names[NUMBER_OF_CONFIGURATION_SETTINGS] PROGMEM =
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
