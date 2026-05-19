#pragma once

#include "src/config/AppConstants.h"

struct Config {
	char deviceId[AppConstants::UUID_MAX_LEN];
	char ssid[AppConstants::SSID_MAX_LEN];
	char password[AppConstants::PASSWORD_MAX_LEN];
	bool configured;
};
