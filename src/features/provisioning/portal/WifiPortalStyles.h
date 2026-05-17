#pragma once

#include <GyverPortal.h>

namespace WifiPortalStyles {

	static const char CSS[] PROGMEM = R"raw(
<style>
  .wifi-portal {
    max-width: 320px;
    margin: 0 auto;
    padding: 16px 0;
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
  }

  .wifi-portal__title {
    margin: 0 0 6px;
    font-size: 22px;
    font-weight: 600;
    color: #2dd4bf;
  }

  .wifi-portal__subtitle {
    margin: 0 0 12px;
    font-size: 14px;
    color: #9ca3af;
  }

  .wifi-portal__url {
    margin: 0 0 16px;
    font-size: 13px;
    color: #6ee7b7;
    white-space: nowrap;
  }

  .wifi-portal__divider {
    margin: 20px 0;
    border: 0;
    border-top: 1px solid #374151;
  }

  .wifi-portal__label {
    display: block;
    margin: 0 0 6px;
    font-size: 13px;
    color: #d1d5db;
  }

  .wifi-portal input.wifi-portal__input {
    display: block;
    box-sizing: border-box;
    width: 100% !important;
    max-width: none !important;
    height: auto !important;
    margin: 0 0 16px;
    padding: 10px 12px;
    font-size: 14px !important;
    color: #f3f4f6;
    background: #1f2937;
    border: 1px solid #374151;
    border-radius: 6px;
  }

  .wifi-portal input.wifi-portal__input::placeholder {
    font-size: 13px !important;
    color: #6b7280;
    opacity: 1;
  }

  .wifi-portal input.wifi-portal__input:focus {
    outline: none;
    border-color: #2dd4bf;
  }

  .wifi-portal__submit {
    width: 100%;
    max-width: 100%;
    height: 39px;
    margin: 0;
    margin-top: 16px;
    padding: 10px;
    font-size: 14px;
    font-weight: 500;
    color: #fff;
    background: #10b981;
    border: none;
    border-radius: 6px;
    cursor: pointer;
  }

  .wifi-portal__submit:active {
    background: #059669;
  }

  #onlBlock.onlBlock {
    display: none !important;
  }
</style>
)raw";

	inline void send() {
		GP.SEND_P(CSS);
	}

}  // namespace WifiPortalStyles
