#include "src/infrastructure/storage/ConfigStorage.h"

#include <string.h>

#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"

namespace ConfigStorage {

	static void load() {
		memset(&g_config, 0, sizeof(g_config));

		g_prefs.begin(AppConstants::PREFS_NAMESPACE, true);
		const size_t len = g_prefs.getBytes(AppConstants::PREFS_KEY_CONFIG, &g_config, sizeof(g_config));
		g_prefs.end();

		if (len != sizeof(g_config)) {
			memset(&g_config, 0, sizeof(g_config));
		}

		g_config.ssid[AppConstants::SSID_MAX_LEN - 1] = '\0';
		g_config.password[AppConstants::PASSWORD_MAX_LEN - 1] = '\0';

		if (strlen(g_config.ssid) == 0) {
			g_config.configured = false;
		}
	}

	void init() {
		load();
	}

	void save() {
		g_prefs.begin(AppConstants::PREFS_NAMESPACE, false);
		g_prefs.putBytes(AppConstants::PREFS_KEY_CONFIG, &g_config, sizeof(g_config));
		g_prefs.end();
	}

	bool isConfigured() {
		return strlen(g_config.ssid) > 0 && g_config.configured;
	}

} // namespace ConfigStorage
