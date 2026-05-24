#include "src/features/fan/FanService.h"

#include <Arduino.h>

#include "src/config/AppConstants.h"

namespace {

    volatile uint32_t pulseCount = 0;
    volatile uint32_t lastPulseUs = 0;

    uint32_t lastRPM = 0;
    uint32_t lastMeasure = 0;

    void IRAM_ATTR onTach() {

        uint32_t now = micros();

        // антидребезг (реально это не дребезг, а фильтр импульсов)
        if (now - lastPulseUs < 2000) {
            return;
        }

        pulseCount++;
        lastPulseUs = now;
    }
}

namespace FanService {

    void begin() {

        ledcAttach(
            AppConstants::FAN_PWM_PIN,
            AppConstants::FAN_PWM_FREQ,
            AppConstants::FAN_PWM_RESOLUTION
        );

        pinMode(
            AppConstants::FAN_TACH_PIN,
            INPUT_PULLUP
        );

        attachInterrupt(
            digitalPinToInterrupt(
                AppConstants::FAN_TACH_PIN
            ),
            onTach,
            FALLING
        );

        setSpeed(0);

        Serial.println("Fan initialized");
    }

    void setSpeed(uint8_t percent) {
        static uint8_t last = 255;
        if (percent == last) return;
        last = percent;

        percent = constrain(percent, 0, 100);

        uint32_t duty = map(percent, 0, 100, 0, 255);
        ledcWrite(AppConstants::FAN_PWM_PIN, duty);
    }

    uint32_t getRPM() {
        uint32_t pulses;
        if (millis() - lastMeasure >= 1000) {

            noInterrupts();
            pulses = pulseCount;
            pulseCount = 0;
            interrupts();

            lastRPM = (pulses * 60) / 2;

            lastMeasure = millis();
        }

        return lastRPM;
    }
}