#include "src/features/provisioning/ProvisionPortal.h"

#include <WiFi.h>

#include "src/app/AppContext.h"
#include "src/config/AppConstants.h"
#include "src/features/provisioning/portal/WifiPortalUI.h"
#include "src/infrastructure/storage/ConfigStorage.h"

namespace ProvisionPortal {

static void buildUi() {
	GP.BUILD_BEGIN();
	GP.THEME(GP_DARK);
	WifiPortalUI::render(g_config, WiFi.softAPIP().toString());
	GP.BUILD_END();
}

static void onAction() {
	if (!g_portal.form(AppConstants::PORTAL_FORM_SAVE)) {
		return;
	}

	g_portal.copyStr("ssid", g_config.ssid, sizeof(g_config.ssid));
	g_portal.copyStr("pass", g_config.password, sizeof(g_config.password));

	g_config.configured = true;
	ConfigStorage::save();

	g_portal.answer(F("Настройки сохранены. Перезагрузка…"));
	delay(AppConstants::REBOOT_DELAY_MS);
	ESP.restart();
}

void start() {
	g_portal.setBufferSize(AppConstants::PORTAL_BUFFER_SIZE);
	g_portal.attachBuild(buildUi);
	g_portal.attach(onAction);
	g_portal.start();
}

void tick() {
	g_portal.tick();
}

}  // namespace ProvisionPortal
