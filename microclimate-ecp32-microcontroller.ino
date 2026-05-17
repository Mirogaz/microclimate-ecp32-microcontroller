#include <ESPmDNS.h>
#include <GyverPortal.h>
#include <Preferences.h>
#include <WiFi.h>
#include <string.h>

#include "HandshakeServer.h"

#include "Config.h"
#include "ModeEnum.h"
#include "WifiPortalUI.h"

#define deviceId "CLIMATRON-V1"

Preferences prefs;
Config cfg;

Mode mode;
GyverPortal ui;

HandshakeServer handshake;

static const char MDNS_HOSTNAME[] = "microclimate";

void startMdns() {
	if (!MDNS.begin(MDNS_HOSTNAME)) {
		Serial.println("mDNS: start failed");
		return;
	}

	MDNS.addService("http", "tcp", 80);

	Serial.print("mDNS: http://");
	Serial.print(MDNS_HOSTNAME);
	Serial.println(".local");
}

void loadConfig() {
	prefs.begin("wifi", true);

	prefs.getBytes("cfg", &cfg, sizeof(cfg));

	prefs.end();

	if (strlen(cfg.ssid) == 0) {
		cfg.configured = false;
	}
}

void initStorage() {
	loadConfig();
}

void saveConfig() {
	prefs.begin("wifi", false);
	prefs.putBytes("cfg", &cfg, sizeof(cfg));
	prefs.end();
}

bool isConfigured() {
	return strlen(cfg.ssid) > 0 && cfg.configured;
}

bool connectWiFi() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(cfg.ssid, cfg.password);

	Serial.print("Connecting");

	int tries = 0;
	while (WiFi.status() != WL_CONNECTED && tries < 20) {
		delay(500);
		Serial.print(".");
		tries++;
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.println("\nConnected!");
		Serial.println(WiFi.localIP());
		startMdns();
		return true;
	}

	Serial.println("\nFailed to connect");
	return false;
}

void startAP() {
	WiFi.mode(WIFI_AP);
	WiFi.softAP("ESP32_SETUP", "12345678");

	Serial.println("AP started");
	Serial.println(WiFi.softAPIP());
	startMdns();
}

void buildUI() {
	GP.BUILD_BEGIN();
	GP.THEME(GP_DARK);
	WifiPortalUI::render(cfg, WiFi.softAPIP().toString());
	GP.BUILD_END();
}

void action() {
	if (!ui.form("/save")) {
		return;
	}

	ui.copyStr("ssid", cfg.ssid, sizeof(cfg.ssid));
	ui.copyStr("pass", cfg.password, sizeof(cfg.password));

	cfg.configured = true;
	saveConfig();

	ui.answer(F("Настройки сохранены. Перезагрузка…"));
	delay(1000);
	ESP.restart();
}

void startPortal() {
	ui.setBufferSize(4096);
	ui.attachBuild(buildUI);
	ui.attach(action);
	ui.start();
}

void setup() {
	Serial.begin(115200);
	initStorage();

	if (!isConfigured()) {
		mode = MODE_PROVISION;
		startAP();
		startPortal();
		return;
	}

	mode = MODE_NORMAL;

	if (connectWiFi()) {

		mode = MODE_HANDSHAKE;

		handshake.begin(&cfg, &mode, deviceId);

		startMdns();

	} else {

		mode = MODE_PROVISION;

		startAP();
		startPortal();
	}
}

void loop() {
	switch (mode) {
	case MODE_PROVISION:
		ui.tick();
		break;
	case MODE_HANDSHAKE:
		handshake.tick();
		break;
	case MODE_NORMAL:
		break;
	}
}
