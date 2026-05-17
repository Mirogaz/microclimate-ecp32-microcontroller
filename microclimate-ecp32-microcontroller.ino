#include "src/app/AppContext.h"
#include "src/features/provisioning/ProvisionPortal.h"
#include "src/infrastructure/network/WiFiConnection.h"
#include "src/infrastructure/storage/ConfigStorage.h"

void setup() {
	Serial.begin(AppConstants::SERIAL_BAUD);
	ConfigStorage::init();

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

	g_mode = MODE_HANDSHAKE;
	g_handshake.begin(&g_config, &g_mode, AppConstants::MDNS_HOSTNAME);
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
		break;
	}
}
