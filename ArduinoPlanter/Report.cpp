
#include "Report.h"

const char PROGMEM text_readings[] = "readings";
const char PROGMEM text_time[] = "time";
const char PROGMEM text_acidity[] = "acidity";
const char PROGMEM text_humidity[] = "humidity";
const char PROGMEM text_temperature[] = "temperature";
const char PROGMEM text_water_on_bottom[] = "water_on_bottom";
const char PROGMEM text_water_on_top[] = "water_on_top";
const char PROGMEM text_remote_control[] = "remote_control";

const char PROGMEM text_state[] = "state";
const char PROGMEM text_decisions[] = "decisions";
const char PROGMEM text_configuration[] = "configuration";

const char PROGMEM text_lamp[] = "lamp";
const char PROGMEM text_pump[] = "pump";
const char PROGMEM text_air_read[] = "air_read";
const char PROGMEM text_action[] = "action";
const char PROGMEM text_reason[] = "reason";
const char PROGMEM text_started[] = "started";
const char PROGMEM text_stopped[] = "stopped";

class JsonSender
{
	/**
	Sends JSON objects over Serial with keys read from PROGMEM
	without building a collection in memory.
	**/
private:
	const char ** keys = NULL;
	int level = 0;
	bool fields_sent = false;

public:
	JsonSender() {} // when using with individual key strings
	JsonSender(const char * const keys [])
	{
		this->keys = (const char **) keys;
	}

	JsonSender & begin(const char * key) // PROGMEM pointer
	{
		this->key(key);
		fields_sent = false;
		return *this;
	}

	JsonSender & value(const char * value) // PROGMEM pointer
	{
		char buffer[SENDER_BUFSIZ + 1];
		strncpy_P(buffer, value, SENDER_BUFSIZ);
		buffer[SENDER_BUFSIZ] = 0;

		Serial.print('"');
		Serial.print(buffer);
		Serial.print('"');
		return *this;
	}

	JsonSender & key(const char * key) // PROGMEM pointer
	{
		if (fields_sent)
		{
			Serial.print(',');
		}
		else
		{
			Serial.print('{');
			fields_sent = true;
			++level;
		}

		value(key);
		Serial.print(':');

		return *this;
	}

	JsonSender & key(int key_index)
	{
		return key((const char *)pgm_read_word(&(keys[key_index])));
	}

	JsonSender & value(const char * const values [], int index)
	{
		return value((const char *)pgm_read_word(&(values[index])));
	}

	template <typename T>
	JsonSender & value(T value)
	{
		Serial.print((T) value);
		return *this;
	}

	JsonSender & value(bool value)
	{
		Serial.print(value ? F("true") : F("false"));
		return *this;
	}

	JsonSender end()
	{
		if (fields_sent)
		{
			Serial.print('}');
		}
		else
		{
			Serial.print(F("null"));
			fields_sent = true;
		}
		--level;
		return *this;
	}

	void finish()
	{
		while (level)
			end();
		Serial.println();
		Serial.flush();
	}
};

class DecisionSender : public JsonSender
{
public:
	DecisionSender & send(const char * name, const enum decision decision)
	{
		if (decision)
		{
			begin(name)
				.key(text_action).value(action_names, decision & 15)
				.key(text_reason).value(reason_descriptions, decision >> 4)
				.end();
		}

		return *this;
	}
};

void Report::sendReadings(readings_t * readings)
{
	JsonSender()
		.begin(text_readings)
		.key(text_time).value(readings->time)
		.key(text_acidity).value(readings->acidity)
		.key(text_humidity).value(readings->humidity)
		.key(text_temperature).value(readings->temperature)
		.key(text_water_on_bottom).value(readings->water_on_bottom)
		.key(text_water_on_top).value(readings->water_on_top)
		.key(text_lamp).value(readings->is_lamp_on)
		.key(text_pump).value(readings->is_pump_on)
		.key(text_remote_control).value(readings->is_remote_control)
		.finish();
}

void Report::sendDecisions(const decisions_t * const decisions)
{
	((DecisionSender&) DecisionSender().begin(text_decisions))
		.send(text_lamp, decisions->turn_lamp_switch)
		.send(text_pump, decisions->turn_pump_switch)
		.send(text_state, decisions->report_state)
		.send(text_configuration, decisions->report_configuration)
		.finish();
}

void Report::sendState(planter_state_t * state)
{
	JsonSender().begin(text_state)
		.begin(text_lamp)
		.key(text_started).value(state->lamp_start_time)
		.key(text_stopped).value(state->lamp_stop_time)
		.end()
		.begin(text_pump)
		.key(text_started).value(state->pump_start_time)
		.key(text_stopped).value(state->pump_stop_time)
		.end()
		.key(text_air_read).value(state->air_read_time)
		.finish();
}

void Report::sendConfiguration(arduino_planter_configuration_t * configuration)
{
	JsonSender(configuration_setting_names)
		.begin(text_configuration)
		.key(CONF_ACIDITY_PIN).value(configuration->acidity_pin)
		.key(CONF_AIR_READ_PIN).value(configuration->air_read_pin)
		.key(CONF_WATER_BOTTOM_PIN).value(configuration->water_bottom_pin)
		.key(CONF_WATER_TOP_PIN).value(configuration->water_top_pin)
		.key(CONF_LAMP_PIN).value(configuration->lamp_pin)
		.key(CONF_PUMP_PIN).value(configuration->pump_pin)
		.key(CONF_LAMP_CYCLE_TIME).value(configuration->lamp_cycle_time)
		.key(CONF_LAMP_ACTIVE_TIME).value(configuration->lamp_active_time)
		.key(CONF_PUMP_CYCLE_TIME).value(configuration->pump_cycle_time)
		.key(CONF_PUMP_ACTIVE_TIME).value(configuration->pump_active_time)
		.key(CONF_AIR_READ_INTERVAL).value(configuration->air_read_interval)
		.key(CONF_REPORT_INTERVAL).value(configuration->report_interval)
		.key(CONF_REMOTE_CONTROL_TIMEOUT).value(configuration->remote_control_timeout)
		.key(CONF_STARTUP_DELAY).value(configuration->startup_delay)
		.key(CONF_SERIAL_PORT_SPEED).value(configuration->serial_port_speed)
		.key(CONF_WATER_SENSOR_VALUE_WHEN_WET).value(configuration->water_sensor_value_when_wet)
		.key(CONF_AIR_SENSOR_TYPE).value(configuration->air_sensor_type)
		.finish();
}
