#pragma once

#include <cstdint>

struct ConfigMQTT {
	String mqttHost;
	uint16_t mqttPort;
	String mqttUsername;
	String mqttPassword;
};
