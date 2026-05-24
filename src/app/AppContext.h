#pragma once

#include <GyverPortal.h>
#include <Preferences.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <OneWire.h>

#include "src/config/Config.h"
#include "src/config/ConfigMQTT.h"
#include "src/domain/Mode.h"
#include "src/features/handshake/HandshakeServer.h"

extern Preferences g_prefs;
extern Config g_config;
extern ConfigMQTT g_configMqtt;
extern Mode g_mode;
extern GyverPortal g_portal;
extern HandshakeServer g_handshake;
extern WiFiClientSecure g_wifiClient;
extern PubSubClient g_mqttClient;