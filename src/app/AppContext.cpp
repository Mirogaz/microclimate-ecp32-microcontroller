#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"

Preferences g_prefs;
Config g_config;
ConfigMQTT g_configMqtt;
Mode g_mode = MODE_PROVISION;
GyverPortal g_portal;
HandshakeServer g_handshake;

WiFiClientSecure g_wifiClient;
PubSubClient g_mqttClient(g_wifiClient);

OneWire g_oneWire(AppConstants::oneWireBus);
DallasTemperature g_sensors(&g_oneWire);