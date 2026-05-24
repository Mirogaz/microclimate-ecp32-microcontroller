#include "src/features/fan/FanService.h"

#include <Arduino.h>

#include "src/config/AppConstants.h"

namespace {

    volatile uint32_t pulseCount = 0;

    uint32_t lastRPM = 0;
    uint32_t lastMeasure = 0;

    void IRAM_ATTR onTach() {

    uint32_t now = micros();

    static uint32_t last = 0;

    if (now - last < 3000) return;  // 3ms минимум

    pulseCount++;
    last = now;
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
        static uint32_t lastTime = 0;
        static uint32_t lastRPMLocal = 0;

        uint32_t now = millis();
        uint32_t dt = now - lastTime;

        if (dt < 1000) {
            return lastRPMLocal;
        }

        noInterrupts();
        uint32_t pulses = pulseCount;
        pulseCount = 0;
        interrupts();

        // RPM = (pulses / PPR) * (60000 / dt)
        lastRPMLocal = (pulses * 60000UL) / (AppConstants::PULSES_PER_REV * dt);

        lastTime = now;

        return lastRPMLocal;
    }
}