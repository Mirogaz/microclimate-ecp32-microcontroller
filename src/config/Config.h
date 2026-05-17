#pragma once

#include "src/config/AppConstants.h"

struct Config {
	char ssid[AppConstants::SSID_MAX_LEN];
	char password[AppConstants::PASSWORD_MAX_LEN];
	bool configured;
};
