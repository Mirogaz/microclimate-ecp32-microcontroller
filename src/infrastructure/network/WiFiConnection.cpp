#include "src/infrastructure/network/WiFiConnection.h"

#include <WiFi.h>

#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"
#include "src/infrastructure/network/MdnsService.h"

namespace WiFiConnection {

	bool connectStation() {
		WiFi.mode(WIFI_STA);
		WiFi.begin(g_config.ssid, g_config.password);

		Serial.print("Connecting");

		for (int tries = 0; tries < AppConstants::WIFI_CONNECT_MAX_TRIES; tries++) {
			if (WiFi.status() == WL_CONNECTED) {
				Serial.println("\nConnected!");
				Serial.println(WiFi.localIP());
				MdnsService::start();
				return true;
			}

			delay(AppConstants::WIFI_RETRY_DELAY_MS);
			Serial.print(".");
		}

		Serial.println("\nFailed to connect");
		return false;
	}

	void startAccessPoint() {
		WiFi.mode(WIFI_AP);
		WiFi.softAP(AppConstants::AP_SSID, AppConstants::AP_PASSWORD);

		Serial.println("AP started");
		Serial.println(WiFi.softAPIP());

		MdnsService::start();
	}

} // namespace WiFiConnection
