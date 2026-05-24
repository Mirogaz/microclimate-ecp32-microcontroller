#pragma once

namespace MQTTService {

	void begin();

	void tick();

	bool connected();

	void publishTemperature(float value);

} 