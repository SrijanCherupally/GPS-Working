#pragma once
#include <Arduino.h>
#include <TinyGPSPlus.h>

namespace gpsModule {
  inline TinyGPSPlus gps;

  inline void begin(uint32_t baud = 38400, HardwareSerial &port = Serial1) {
    port.begin(baud);
    Serial.println("GPS ready");
  }

  inline void update(HardwareSerial &port = Serial1) {
    while (port.available()) {
      gps.encode(port.read());
    }
  }

  inline void printLocation() {
    if (gps.location.isUpdated()) {
      Serial.print("Lat: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Lon: ");
      Serial.print(gps.location.lng(), 6);
      Serial.print(" Sats: ");
      Serial.println(gps.satellites.value());
    }
  }
}
