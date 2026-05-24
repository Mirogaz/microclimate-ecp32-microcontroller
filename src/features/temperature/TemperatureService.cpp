#include "src/app/AppContext.h"
#include "src/features/temperature/TemperatureService.h"

namespace TemperatureService {

	void begin() {
		g_sensors.begin();
	}

	float read() {

		g_sensors.requestTemperatures();

		return g_sensors.getTempCByIndex(0);
	}
}