#include "src/app/AppContext.h"
#include "src/features/provisioning/ProvisionPortal.h"
#include "src/infrastructure/network/WiFiConnection.h"
#include "src/infrastructure/storage/ConfigMqttStorage.h"
#include "src/infrastructure/storage/ConfigStorage.h"

void setup() {
	Serial.begin(AppConstants::SERIAL_BAUD);
	// нужна небольшая задержка что бы serial успел стартануть
	delay(1000);
	ConfigStorage::init();
	ConfigMqttStorage::init();

	if (!ConfigStorage::isConfigured()) {
		g_mode = MODE_PROVISION;
		WiFiConnection::startAccessPoint();
		ProvisionPortal::start();
		return;
	}

	if (!WiFiConnection::connectStation()) {
		g_mode = MODE_PROVISION;
		WiFiConnection::startAccessPoint();
		ProvisionPortal::start();
		return;
	}
	// TODO: добавить сюда проверку на попытку соединения с mqtt
	if (!ConfigMqttStorage::isConfigured()) {
		g_mode = MODE_HANDSHAKE;
		g_handshake.begin(&g_config, &g_mode, AppConstants::DEVICE_NAME);
	}

	if (ConfigMqttStorage::isConfigured() && ConfigStorage::isConfigured()) {
		g_mode = MODE_NORMAL;
	}
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
		// g_handshake.tick();
		break;
	}
}
