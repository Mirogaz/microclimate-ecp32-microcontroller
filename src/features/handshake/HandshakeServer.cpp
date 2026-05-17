#include "src/features/handshake/HandshakeServer.h"

#include <Arduino_JSON.h>
#include <WiFi.h>

#include "src/config/AppConstants.h"
#include "src/config/ConfigMQTT.h"
#include "src/utils/FieldsJSON.h"

ConfigMQTT configMQTT;

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

	bool hasMqttHost = FieldsJSON::hasNonEmptyString(doc, "mqttHost");
	bool hasMqttUsername = FieldsJSON::hasNonEmptyString(doc, "mqttUsername");
	bool hasMqttPassword = FieldsJSON::hasNonEmptyString(doc, "mqttPassword");
	bool hasMqttPort = FieldsJSON::hasNonEmptyNumber(doc, "mqttPort");

	if (!hasMqttHost || !hasMqttUsername || !hasMqttPassword || !hasMqttPort) {
		server.send(400, "application/json",
		            "{\"status\":\"error\",\"message\":\"Required: mqttHost, mqttUsername, mqttPassword (non-empty "
		            "strings), mqttPort (1-65535)\"}");
		return;
	}

	Serial.println("Registration complete");

	configMQTT.mqttHost = static_cast<const char*>(doc["mqttHost"]);
	configMQTT.mqttPort = static_cast<uint16_t>(static_cast<int>(doc["mqttPort"]));
	configMQTT.mqttUsername = static_cast<const char*>(doc["mqttUsername"]);
	configMQTT.mqttPassword = static_cast<const char*>(doc["mqttPassword"]);

	Serial.println("MQTT config:");
	Serial.print("  host: ");
	Serial.println(configMQTT.mqttHost);
	Serial.print("  port: ");
	Serial.println(configMQTT.mqttPort);
	Serial.print("  username: ");
	Serial.println(configMQTT.mqttUsername);
	Serial.print("  password: ");
	Serial.println(configMQTT.mqttPassword);

	server.send(200, "application/json", "{\"status\":\"ok\"}");
}
