#include <Arduino.h>
#include "gps.h"
#include "imu_icm42688.h"
#include "dps368.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  gpsModule::begin();
  icm42688::begin();
  dps368::begin();

  Serial.println("Sensor system initialized");
}

void loop() {
  gpsModule::update();
  gpsModule::printLocation();

  icm42688::update();
  icm42688::printReading();

  dps368::update();
  dps368::printPressureTemperature();
}
