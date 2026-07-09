#pragma once
#include <Arduino.h>

namespace icm42688 {
  inline bool initialized = false;

  inline void begin() {
    initialized = true;
    Serial.println("ICM42688 interface ready");
  }

  inline void update() {
    if (!initialized) {
      return;
    }
  }

  inline void printReading() {
    if (!initialized) {
      return;
    }

    Serial.println("ICM42688: placeholder data");
  }
}
