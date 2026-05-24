#include "src/infrastructure/network/MdnsService.h"

#include <ESPmDNS.h>

#include "src/config/AppConstants.h"

namespace MdnsService {

	void start() {
		if (!MDNS.begin(AppConstants::MDNS_HOSTNAME)) {
			Serial.println("mDNS: start failed");
			return;
		}

		MDNS.addService("http", "tcp", AppConstants::HTTP_PORT);

		Serial.print("mDNS: http://");
		Serial.print(AppConstants::MDNS_HOSTNAME);
		Serial.println(".local");
	}

} // namespace MdnsService
