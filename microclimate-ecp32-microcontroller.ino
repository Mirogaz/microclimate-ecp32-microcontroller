#include "src/app/AppContext.h"
#include "src/features/provisioning/ProvisionPortal.h"
#include "src/features/temperature/TemperatureService.h"
#include "src/infrastructure/network/MQTTService.h"
#include "src/infrastructure/network/WiFiConnection.h"
#include "src/infrastructure/storage/ConfigMqttStorage.h"
#include "src/infrastructure/storage/ConfigStorage.h"

void setup() {
	Serial.begin(AppConstants::SERIAL_BAUD);
	delay(1000);
	ConfigStorage::init();
	ConfigMqttStorage::init();
	TemperatureService::begin();
	FanService::begin();

	if (!ConfigStorage::isConfigured()) {
		g_mode = MODE_PROVISION;
		WiFiConnection::startAccessPoint();
		ProvisionPortal::start();
		return;
	}

	bool wifiOk = WiFiConnection::connectStation();

	if (!wifiOk) {
		g_mode = MODE_PROVISION;
		WiFiConnection::startAccessPoint();
		ProvisionPortal::start();
		return;
	}

	configTime(0, 0, "pool.ntp.org");

	Serial.print("Waiting for NTP");

	time_t now = time(nullptr);

	while (now < 100000) {
		delay(500);
		Serial.print(".");
		now = time(nullptr);
	}

	Serial.println("\nTime synced");

	if (!ConfigMqttStorage::isConfigured()) {

		g_mode = MODE_HANDSHAKE;

		g_handshake.begin(&g_config, &g_mode, AppConstants::DEVICE_NAME);

		return;
	}

	MQTTService::begin();

	g_mode = MODE_NORMAL;
}

void loop() {
	switch (g_mode) {
	case MODE_PROVISION:
		ProvisionPortal::tick();
		break;
	case MODE_HANDSHAKE:
		g_handshake.tick();
		break;
	case MODE_NORMAL:
		MQTTService::tick();
		static uint8_t speed = 0;
		static uint32_t lastTelemetry = 0;
		static uint32_t lastFanUpdate = 0;

		// 1. температура
		if (millis() - lastTelemetry > AppConstants::MQTT_DELAY) {
			float temp = TemperatureService::read();
			MQTTService::publishTemperature(temp);
			lastTelemetry = millis();
		}
		
		// 2. вентилятор + RPM + MQTT
		if (millis() - lastFanUpdate > AppConstants::MQTT_DELAY) {

			FanService::setSpeed(speed);

			uint32_t rpm = FanService::getRPM();

			Serial.print("current speed: ");
			Serial.println(speed);

			Serial.print("current rpm: ");
			Serial.println(rpm);

			MQTTService::publishFan(speed, rpm);

			// speed += 25;
			if (speed > 100) {
				speed = 0;
			}

			lastFanUpdate = millis();
		}

		break;
	}
}
