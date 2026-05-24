#pragma once

namespace MQTTService {

	void begin();

	void tick();

	bool connected();

	void publishTemperature(float value);

	void publishFan(uint8_t speed, uint32_t rpm);

} 