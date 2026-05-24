#include "src/features/temperature/TemperatureService.h"

namespace TemperatureService {

	void begin() {
	}

	float read() {
		// TODO: write reading temperature 

		static float temp = 22.0;

		temp += 0.1;

		if (temp > 30) {
			temp = 22;
		}

		return temp;
	}
}