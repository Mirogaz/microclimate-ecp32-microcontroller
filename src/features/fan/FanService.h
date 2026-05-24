#pragma once

#include <stdint.h>

namespace FanService {

    void begin();

    void setSpeed(uint8_t percent);

    uint32_t getRPM();

}