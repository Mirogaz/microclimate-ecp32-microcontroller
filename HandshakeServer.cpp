#include "HandshakeServer.h"

#include <Arduino_JSON.h>
#include <WiFi.h>

void HandshakeServer::begin(
    Config* config,
    Mode* currentMode,
    const char* name
) {

    cfg = config;
    mode = currentMode;
    deviceName = name;

    server.on(
        "/handshake",
        HTTP_GET,
        [this]() {
            handleGet();
        }
    );

    server.on(
        "/handshake",
        HTTP_POST,
        [this]() {
            handlePost();
        }
    );

    server.begin();

    Serial.println("Handshake server started");
}

void HandshakeServer::tick() {
    server.handleClient();
}

void HandshakeServer::handleGet() {

    JSONVar json;

    json["deviceName"] = deviceName;
    json["mac"] = WiFi.macAddress();
    json["ip"] = WiFi.localIP().toString();

    server.send(
        200,
        "application/json",
        JSON.stringify(json)
    );
}

void HandshakeServer::handlePost() {

    Serial.println("Registration complete");

    *mode = MODE_NORMAL;

    server.send(
        200,
        "application/json",
        "{\"status\":\"ok\"}"
    );
}