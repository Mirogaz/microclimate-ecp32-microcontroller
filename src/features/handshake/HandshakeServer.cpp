#include "src/features/handshake/HandshakeServer.h"

#include <Arduino_JSON.h>
#include <WiFi.h>

#include "src/config/AppConstants.h"

HandshakeServer::HandshakeServer() : server(AppConstants::HTTP_PORT) {}

void HandshakeServer::begin(Config* config, Mode* currentMode, const char* id) {
	cfg = config;
	mode = currentMode;
	deviceId = id;

	server.on(AppConstants::HANDSHAKE_PATH, HTTP_GET, [this]() { handleGet(); });
	server.on(AppConstants::HANDSHAKE_PATH, HTTP_POST, [this]() { handlePost(); });

	server.begin();

	Serial.println("Handshake server started");
}

void HandshakeServer::tick() {
	server.handleClient();
}

void HandshakeServer::handleGet() {
	JSONVar json;

	json["deviceId"] = deviceId;
	json["mac"] = WiFi.macAddress();
	json["ip"] = WiFi.localIP().toString();

	server.send(200, "application/json", JSON.stringify(json));
}

void HandshakeServer::handlePost() {
	Serial.println("Registration complete");

	*mode = MODE_NORMAL;

	server.send(200, "application/json", "{\"status\":\"ok\"}");
}
