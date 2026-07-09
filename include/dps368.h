#pragma once
#include <Arduino.h>

namespace dps368 {
  inline bool initialized = false;

  inline void begin() {
    initialized = true;
    Serial.println("DPS368 interface ready");
  }

  inline void update() {
    if (!initialized) {
      return;
    }
  }

  inline void printPressureTemperature() {
    if (!initialized) {
      return;
    }

    Serial.println("DPS368: placeholder pressure/temperature");
  }
}
