#pragma once

#include <cstddef>
#include <cstdint>

namespace AppConstants {

	inline constexpr char DEVICE_NAME[] = "CLIMATRON-V0";
	inline constexpr char MDNS_HOSTNAME[] = "microclimate";

	inline constexpr char AP_SSID[] = "ESP32_SETUP";
	inline constexpr char AP_PASSWORD[] = "12345678";

	inline constexpr char PREFS_NAMESPACE[] = "pref";

	inline constexpr char MQTT_HOST_KEY[] = "mqtt_host";
	inline constexpr char MQTT_PORT_KEY[] = "mqtt_port";
	inline constexpr char MQTT_USER_KEY[] = "mqtt_user";
	inline constexpr char MQTT_PASSWORD_KEY[] = "mqtt_pass";

	inline constexpr char PREFS_KEY_CONFIG[] = "cfg";

	inline constexpr char PORTAL_FORM_SAVE[] = "/save";
	inline constexpr char HANDSHAKE_PATH[] = "/handshake";

	inline constexpr size_t SSID_MAX_LEN = 32;
	inline constexpr size_t PASSWORD_MAX_LEN = 64;
	inline constexpr size_t UUID_MAX_LEN = 64;

	inline constexpr int WIFI_CONNECT_MAX_TRIES = 20;
	inline constexpr uint32_t WIFI_RETRY_DELAY_MS = 500;

	inline constexpr uint32_t SERIAL_BAUD = 115200;
	inline constexpr size_t PORTAL_BUFFER_SIZE = 4096;
	inline constexpr uint16_t HTTP_PORT = 80;
	inline constexpr uint32_t REBOOT_DELAY_MS = 1000;
	inline constexpr int TELEMETRY_DELAY = 5000;

	inline constexpr int oneWireBus = 22;

	inline constexpr uint8_t FAN_PWM_PIN = 18;
	inline constexpr uint8_t FAN_TACH_PIN = 19;
	inline constexpr uint32_t FAN_PWM_FREQ = 25000;
	inline constexpr uint8_t FAN_PWM_RESOLUTION = 8;

} // namespace AppConstants
