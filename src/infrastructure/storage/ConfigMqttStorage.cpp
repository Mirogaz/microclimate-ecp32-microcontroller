#include "src/infrastructure/storage/ConfigMqttStorage.h"

#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"

namespace ConfigMqttStorage {

	static void load() {
        Serial.println("MQTT config loading...");

		g_prefs.begin(
			AppConstants::PREFS_NAMESPACE,
			true
		);

		g_configMqtt.mqttHost =
			g_prefs.getString(
				AppConstants::MQTT_HOST_KEY,
				""
			);

		g_configMqtt.mqttPort =
			g_prefs.getUShort(
				AppConstants::MQTT_PORT_KEY,
				0
			);

		g_configMqtt.mqttUsername =
			g_prefs.getString(
				AppConstants::MQTT_USER_KEY,
				""
			);

		g_configMqtt.mqttPassword =
			g_prefs.getString(
				AppConstants::MQTT_PASSWORD_KEY,
				""
			);

		g_prefs.end();
	}

	void init() {
		load();
        if(isConfigured()) {
            Serial.println("===== MQTT CONFIG =====");

            Serial.print("host: ");
            Serial.println(g_configMqtt.mqttHost);

            Serial.print("port: ");
            Serial.println(g_configMqtt.mqttPort);

            Serial.print("username: ");
            Serial.println(g_configMqtt.mqttUsername);

            Serial.print("password: ");
            Serial.println(g_configMqtt.mqttPassword);

            Serial.println("=======================");
        } else{
            Serial.println("Mqtt config is not configured");
        }
	}

	void save() {

		g_prefs.begin(
			AppConstants::PREFS_NAMESPACE,
			false
		);

		g_prefs.putString(
			AppConstants::MQTT_HOST_KEY,
			g_configMqtt.mqttHost
		);

		g_prefs.putUShort(
			AppConstants::MQTT_PORT_KEY,
			g_configMqtt.mqttPort
		);

		g_prefs.putString(
			AppConstants::MQTT_USER_KEY,
			g_configMqtt.mqttUsername
		);

		g_prefs.putString(
			AppConstants::MQTT_PASSWORD_KEY,
			g_configMqtt.mqttPassword
		);

		g_prefs.end();
	}

	bool isConfigured() {

		return
			!g_configMqtt.mqttHost.isEmpty() &&
			g_configMqtt.mqttPort > 0;
	}

}