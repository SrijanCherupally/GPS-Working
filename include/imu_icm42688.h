#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <ICM42688.h>

namespace icm42688 {
  inline ICM42688 imu(Wire, 0x68);
  inline bool initialized = false;
  inline float accelX = 0.0f;
  inline float accelY = 0.0f;
  inline float accelZ = 0.0f;
  inline float gyroX = 0.0f;
  inline float gyroY = 0.0f;
  inline float gyroZ = 0.0f;
  inline float temperatureC = 0.0f;

  inline bool begin() {
    Wire.begin();

    int status = imu.begin();
    if (status != 0) {
      Serial.print("ICM42688 begin failed with status: ");
      Serial.println(status);
      initialized = false;
      return false;
    }

    imu.setAccelFS(ICM42688::AccelFS::gpm8);
    imu.setGyroFS(ICM42688::GyroFS::dps500);
    imu.setAccelODR(ICM42688::ODR::odr100);
    imu.setGyroODR(ICM42688::ODR::odr100);
    imu.setFilters(true, true);

    initialized = true;
    Serial.println("ICM42688 ready");
    return true;
  }

  inline bool update() {
    if (!initialized) {
      return false;
    }

    if (imu.getAGT() < 0) {
      return false;
    }

    accelX = imu.accX();
    accelY = imu.accY();
    accelZ = imu.accZ();
    gyroX = imu.gyrX();
    gyroY = imu.gyrY();
    gyroZ = imu.gyrZ();
    temperatureC = imu.temp();
    return true;
  }

  inline void printReading() {
    if (!initialized) {
      return;
    }

    Serial.print("IMU accel(g): ");
    Serial.print(accelX, 3);
    Serial.print(", ");
    Serial.print(accelY, 3);
    Serial.print(", ");
    Serial.print(accelZ, 3);
    Serial.print(" | gyro(dps): ");
    Serial.print(gyroX, 3);
    Serial.print(", ");
    Serial.print(gyroY, 3);
    Serial.print(", ");
    Serial.print(gyroZ, 3);
    Serial.print(" | temp(C): ");
    Serial.println(temperatureC, 2);
  }

  inline void printSettings() {
    if (!initialized) {
      return;
    }

    Serial.println("ICM42688 settings: accel FS = 8g, gyro FS = 500 dps, ODR = 100 Hz");
  }
}
