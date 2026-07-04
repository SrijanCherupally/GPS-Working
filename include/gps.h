#include <Arduino.h>
#include <TinyGPSPlus.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial1.begin(38400);
  Serial.println("GPS running");
}

void loop() {
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Lon: ");
    Serial.print(gps.location.lng(), 6);
    Serial.print(" Sats: ");
    Serial.println(gps.satellites.value());
  }
}
