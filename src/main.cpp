#include <Arduino.h>
#include "gps.h"
#include "imu_icm42688.h"
#include "sensor_dps368.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  constexpr int IMU_CS_PIN = 17;
  constexpr int IMU_SCLK_PIN = 18;
  constexpr int IMU_MISO_PIN = 16;
  constexpr int IMU_MOSI_PIN = 19;
  constexpr int DPS_CS_PIN = 16;
  constexpr int DPS_SCLK_PIN = 18;
  constexpr int DPS_MISO_PIN = 20;
  constexpr int DPS_MOSI_PIN = 19;

  gpsModule::begin();
  icm42688::begin(IMU_CS_PIN, IMU_SCLK_PIN, IMU_MISO_PIN, IMU_MOSI_PIN);
  dps368::begin(DPS_CS_PIN, DPS_SCLK_PIN, DPS_MISO_PIN, DPS_MOSI_PIN);

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
