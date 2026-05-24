#include "src/app/AppContext.h"
#include "src/infrastructure/network/MQTTService.h"

namespace MQTTService {

	static uint32_t lastReconnectAttempt = 0;

	void begin() {

		g_wifiClient.setInsecure();

		Serial.println("Testing TCP...");

		bool ok = g_wifiClient.connect(
			g_configMqtt.mqttHost.c_str(),
			g_configMqtt.mqttPort
		);

		if (!ok) {
			Serial.println("TCP FAILED");
		} else {
			Serial.println("TCP OK");
			g_wifiClient.stop();
		}

		g_mqttClient.setServer(
			g_configMqtt.mqttHost.c_str(),
			g_configMqtt.mqttPort
		);
	}

	bool connected() {
		return g_mqttClient.connected();
	}

	static void reconnect() {

		if (millis() - lastReconnectAttempt < 5000) {
			return;
		}

		lastReconnectAttempt = millis();

		Serial.println("MQTT connecting...");

		bool ok = g_mqttClient.connect(
			g_config.deviceId,
			g_configMqtt.mqttUsername.c_str(),
			g_configMqtt.mqttPassword.c_str()
		);

		if (!ok) {
			Serial.println("MQTT connect failed");

			Serial.print("MQTT state: ");
			Serial.println(g_mqttClient.state());	
			return;
		}

		Serial.println("MQTT connected");
	}

	void tick() {

		if (!g_mqttClient.connected()) {
			reconnect();
			return;
		}

		g_mqttClient.loop();
	}

	void publishTemperature(float value) {

		if (!connected()) {
			return;
		}

		String topic =
			String("devices/") +
			g_config.deviceId +
			"/temperature";	

		String payload = String(value);

		g_mqttClient.publish(
			topic.c_str(),
			payload.c_str(),
			true
		);

		Serial.print("Published: ");
		Serial.println(payload);
	}

	void publishFan(uint8_t speed, uint32_t rpm) {

		if (!connected()) return;

		String topic =
			String("devices/") +
			g_config.deviceId +
			"/fan";

		String payload =
			String("{\"speed\":") +
			speed +
			",\"rpm\":" +
			rpm +
			"}";

		g_mqttClient.publish(topic.c_str(), payload.c_str(), true);
	}
}