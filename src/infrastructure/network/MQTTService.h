#pragma once

namespace MQTTService {

	void begin();

	void tick();

	bool connected();

	void publishTemperature(float value);

	void publishFan(uint32_t rpm);

	void mqttCallback(char* topic, byte* payload, unsigned int length);

} 