#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <ICM42688.h>

namespace icm42688 {
  inline ICM42688 imu(SPI, 17);
  inline bool initialized = false;
  inline int csPin = 9;
  inline int sclkPin = 10;
  inline int misoPin = 8;
  inline int mosiPin = 11;
  inline float accelX = 0.0f;
  inline float accelY = 0.0f;
  inline float accelZ = 0.0f;
  inline float gyroX = 0.0f;
  inline float gyroY = 0.0f;
  inline float gyroZ = 0.0f;
  inline float temperatureC = 0.0f;

  inline bool begin(int chipSelectPin = 17, int clockPin = 18, int misoPinNumber = 16, int mosiPinNumber = 19) {
    csPin = chipSelectPin;
    sclkPin = clockPin;
    misoPin = misoPinNumber;
    mosiPin = mosiPinNumber;

    SPI.begin();
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    delay(50);

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
    Serial.print("ICM42688 ready on CS=");
    Serial.print(csPin);
    Serial.print(" SCLK=");
    Serial.print(sclkPin);
    Serial.print(" MISO=");
    Serial.print(misoPin);
    Serial.print(" MOSI=");
    Serial.println(mosiPin);
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
