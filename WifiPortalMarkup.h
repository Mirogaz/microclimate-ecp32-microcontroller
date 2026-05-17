#pragma once

#include <GyverPortal.h>

namespace WifiPortalMarkup {

	static const char HEADER_START[] PROGMEM = R"raw(
		<div class="wifi-portal">
		<h1 class="wifi-portal__title">Микроклимат</h1>
		<p class="wifi-portal__subtitle">Подключение к домашней Wi-Fi сети</p>
		<p class="wifi-portal__url">Адрес: http://
	)raw";

	static const char HEADER_END[] PROGMEM = R"raw(
		</p>
		<hr class="wifi-portal__divider">
	)raw";

	static const char FORM_SSID_START[] PROGMEM = R"raw(
		<label class="wifi-portal__label" for="ssid">Имя сети (SSID)</label>
		<input
			class="wifi-portal__input"
			id="ssid"
			name="ssid"
			type="text"
			maxlength="32"
			placeholder="Название сети"
	)raw";

	static const char FORM_PASS_START[] PROGMEM = R"raw(
		<label class="wifi-portal__label" for="pass">Пароль Wi-Fi</label>
		<input
			class="wifi-portal__input"
			id="pass"
			name="pass"
			type="password"
			maxlength="64"
			placeholder="Пароль"
	)raw";

	static const char FORM_END[] PROGMEM = R"raw(
		<button class="wifi-portal__submit" type="submit">Сохранить</button>
	)raw";

	static const char PAGE_END[] PROGMEM = R"raw(
		</div>
	)raw";

	inline void sendHeaderStart() {
		GP.SEND_P(HEADER_START);
	}

	inline void sendHeaderEnd() {
		GP.SEND_P(HEADER_END);
	}

	inline void sendFormSsidStart() {
		GP.SEND_P(FORM_SSID_START);
	}

	inline void sendFormPassStart() {
		GP.SEND_P(FORM_PASS_START);
	}

	inline void sendFormEnd() {
		GP.SEND_P(FORM_END);
	}

	inline void sendPageEnd() {
		GP.SEND_P(PAGE_END);
	}

} // namespace WifiPortalMarkup
