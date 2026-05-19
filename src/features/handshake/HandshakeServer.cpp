#include "src/features/handshake/HandshakeServer.h"

#include <Arduino_JSON.h>
#include <WiFi.h>

#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"
#include "src/infrastructure/storage/ConfigMqttStorage.h"
#include "src/utils/FieldsJSON.h"

HandshakeServer::HandshakeServer() : server(AppConstants::HTTP_PORT) {}

void HandshakeServer::begin(Config* config, Mode* currentMode, const char* name) {
	cfg = config;
	mode = currentMode;
	deviceName = name;

	server.on(AppConstants::HANDSHAKE_PATH, HTTP_GET, [this]() { handleGet(); });
	server.on(AppConstants::HANDSHAKE_PATH, HTTP_POST, [this]() { handlePost(); });

	server.begin();

	Serial.println("Handshake server started");
	Serial.print("Handshake URL: http://");
	Serial.print(WiFi.localIP());
	Serial.println(AppConstants::HANDSHAKE_PATH);
}

void HandshakeServer::tick() {
	server.handleClient();
}

void HandshakeServer::handleGet() {
	JSONVar json;

	json["deviceName"] = deviceName;
	json["mac"] = WiFi.macAddress();
	json["ip"] = WiFi.localIP().toString();

	server.send(200, "application/json", JSON.stringify(json));
}

void HandshakeServer::handlePost() {
	if (!server.hasArg("plain")) {
		server.send(400, "application/json",
		            "{\"status\":\"error\",\"message\":\"Expected JSON body (Content-Type: application/json)\"}");
		return;
	}

	JSONVar doc = JSON.parse(server.arg("plain"));

	if (FieldsJSON::isUndefined(doc)) {
		server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
		return;
	}

	bool hasDeviceId = FieldsJSON::hasNonEmptyString(doc, "deviceId");
	bool hasMqttHost = FieldsJSON::hasNonEmptyString(doc, "mqttHost");
	bool hasMqttUsername = FieldsJSON::hasNonEmptyString(doc, "mqttUsername");
	bool hasMqttPassword = FieldsJSON::hasNonEmptyString(doc, "mqttPassword");
	bool hasMqttPort = FieldsJSON::hasNonEmptyNumber(doc, "mqttPort");

	bool hasAllFields = hasDeviceId && hasMqttHost && hasMqttUsername && hasMqttPassword && hasMqttPort;

	if (!hasAllFields) {
		server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Required: deviceId, mqttHost, mqttUsername, mqttPassword, mqttPort\"}");
		return;
	}

	g_config.deviceId = static_cast<const char*>(doc["deviceId"]);

	Serial.println("Registration complete");

	g_configMqtt.mqttHost = static_cast<const char*>(doc["mqttHost"]);
	g_configMqtt.mqttPort = static_cast<uint16_t>(static_cast<int>(doc["mqttPort"]));
	g_configMqtt.mqttUsername = static_cast<const char*>(doc["mqttUsername"]);
	g_configMqtt.mqttPassword = static_cast<const char*>(doc["mqttPassword"]);

	Serial.println("MQTT config:");
	Serial.print("  deviceId: ");
	Serial.println(g_config.deviceId);
	Serial.print("  host: ");
	Serial.println(g_configMqtt.mqttHost);
	Serial.print("  port: ");
	Serial.println(g_configMqtt.mqttPort);
	Serial.print("  username: ");
	Serial.println(g_configMqtt.mqttUsername);
	Serial.print("  password: ");
	Serial.println(g_configMqtt.mqttPassword);

	ConfigMqttStorage::save();

	server.send(200, "application/json", "{\"status\":\"ok\"}");
}
