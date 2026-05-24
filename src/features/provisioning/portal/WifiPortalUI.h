#pragma once

#include "src/config/AppConstants.h"
#include "src/config/Config.h"
#include "src/features/provisioning/portal/WifiPortalMarkup.h"
#include "src/features/provisioning/portal/WifiPortalStyles.h"
#include <GyverPortal.h>

namespace WifiPortalUI {

	static void sendHtmlAttr(const char* value) {
		for (const char* p = value; *p; p++) {
			switch (*p) {
			case '&':
				GP.SEND(F("&amp;"));
				break;
			case '"':
				GP.SEND(F("&quot;"));
				break;
			case '<':
				GP.SEND(F("&lt;"));
				break;
			case '>':
				GP.SEND(F("&gt;"));
				break;
			default: {
				const char ch[2] = {*p, '\0'};
				GP.SEND(ch);
			}
			}
		}
	}

	static void sendInputClose(const char* value) {
		if (value[0] != '\0') {
			GP.SEND(F(" value=\""));
			sendHtmlAttr(value);
			GP.SEND(F("\""));
		}
		GP.SEND(F(">\n"));
	}

	static void sendHeader(const String& apIp) {
		WifiPortalMarkup::sendHeaderStart();
		GP.SEND(apIp);
		WifiPortalMarkup::sendHeaderEnd();
	}

	static void sendFormFields(const Config& config) {
		WifiPortalMarkup::sendFormSsidStart();
		sendInputClose(config.ssid);

		WifiPortalMarkup::sendFormPassStart();
		sendInputClose(config.password);

		WifiPortalMarkup::sendFormEnd();
	}

	static void render(const Config& config, const String& apIp) {
		WifiPortalStyles::send();
		sendHeader(apIp);
		GP.FORM_BEGIN(AppConstants::PORTAL_FORM_SAVE);
		sendFormFields(config);
		GP.FORM_END();
		WifiPortalMarkup::sendPageEnd();
	}

} // namespace WifiPortalUI
