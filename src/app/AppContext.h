#pragma once

#include <GyverPortal.h>
#include <Preferences.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "src/config/Config.h"
#include "src/config/ConfigMQTT.h"
#include "src/domain/Mode.h"
#include "src/features/handshake/HandshakeServer.h"
#include "src/features/fan/FanService.h"

extern Preferences g_prefs;
extern Config g_config;
extern ConfigMQTT g_configMqtt;
extern Mode g_mode;
extern GyverPortal g_portal;
extern HandshakeServer g_handshake;
// TODO: сменить, наверное, потом клиент на (что бы был без TLS):
//  #include <WiFiClient.h>
extern WiFiClientSecure g_wifiClient;
extern PubSubClient g_mqttClient;

extern OneWire g_oneWire;
extern DallasTemperature g_sensors;