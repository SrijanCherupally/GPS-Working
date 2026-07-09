#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <Dps3xx.h>

namespace dps368 {
  inline Dps3xx sensor;
  inline bool initialized = false;
  inline int csPin = 17;
  inline int sclkPin = 18;
  inline int misoPin = 16;
  inline int mosiPin = 19;
  inline uint8_t slaveAddress = 0x77;
  inline float temperatureC = 0.0f;
  inline float pressurePa = 0.0f;
  inline float altitudeM = 0.0f;
  inline float seaLevelPressureHpa = 1013.25f;
  inline uint8_t tempMr = DPS__MEASUREMENT_RATE_8;
  inline uint8_t tempOsr = DPS__OVERSAMPLING_RATE_8;
  inline uint8_t prsMr = DPS__MEASUREMENT_RATE_8;
  inline uint8_t prsOsr = DPS__OVERSAMPLING_RATE_8;

  inline bool begin(int chipSelectPin = 16, int clockPin = 18, int misoPinNumber = 20, int mosiPinNumber = 19, uint8_t address = 0x77) {
    csPin = chipSelectPin;
    sclkPin = clockPin;
    misoPin = misoPinNumber;
    mosiPin = mosiPinNumber;
    slaveAddress = address;

    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    Wire.begin();
    delay(50);
    sensor.begin(Wire, slaveAddress);
    sensor.correctTemp();

    initialized = true;
    Serial.print("DPS368 ready on CS=");
    Serial.print(csPin);
    Serial.print(" SCLK=");
    Serial.print(sclkPin);
    Serial.print(" MISO=");
    Serial.print(misoPin);
    Serial.print(" MOSI=");
    Serial.print(mosiPin);
    Serial.print(" addr=0x");
    Serial.println(slaveAddress, HEX);
    return true;
  }

  inline int16_t setStandbyMode() {
    if (!initialized) {
      return DPS__FAIL_INIT_FAILED;
    }
    return sensor.standby();
  }

  inline int16_t setSingleTemperatureMode() {
    if (!initialized) {
      return DPS__FAIL_INIT_FAILED;
    }
    return sensor.startMeasureTempOnce();
  }

  inline int16_t setSinglePressureMode() {
    if (!initialized) {
      return DPS__FAIL_INIT_FAILED;
    }
    return sensor.startMeasurePressureOnce();
  }

  inline int16_t setContinuousBothMode(uint8_t tempMrValue = DPS__MEASUREMENT_RATE_8,
                                       uint8_t tempOsrValue = DPS__OVERSAMPLING_RATE_8,
                                       uint8_t prsMrValue = DPS__MEASUREMENT_RATE_8,
                                       uint8_t prsOsrValue = DPS__OVERSAMPLING_RATE_8) {
    if (!initialized) {
      return DPS__FAIL_INIT_FAILED;
    }

    tempMr = tempMrValue;
    tempOsr = tempOsrValue;
    prsMr = prsMrValue;
    prsOsr = prsOsrValue;

    return sensor.startMeasureBothCont(tempMr, tempOsr, prsMr, prsOsr);
  }

  inline bool measureTemperature(float &outTemp) {
    if (!initialized) {
      return false;
    }

    int16_t status = sensor.measureTempOnce(outTemp);
    if (status == DPS__SUCCEEDED) {
      temperatureC = outTemp;
      return true;
    }

    return false;
  }

  inline bool measurePressure(float &outPressure) {
    if (!initialized) {
      return false;
    }

    int16_t status = sensor.measurePressureOnce(outPressure);
    if (status == DPS__SUCCEEDED) {
      pressurePa = outPressure;
      return true;
    }

    return false;
  }

  inline float calculateAltitudeMeters(float pressureHpa, float seaLevelPressure = 1013.25f) {
    if (pressureHpa <= 0.0f) {
      return 0.0f;
    }

    return 44330.0f * (1.0f - powf(pressureHpa / seaLevelPressure, 1.0f / 5.255f));
  }

  inline bool update() {
    if (!initialized) {
      return false;
    }

    float temp = 0.0f;
    float pressure = 0.0f;

    if (!measureTemperature(temp)) {
      return false;
    }

    if (!measurePressure(pressure)) {
      return false;
    }

    altitudeM = calculateAltitudeMeters(pressure / 100.0f, seaLevelPressureHpa);
    return true;
  }

  inline void printPressureTemperature() {
    if (!initialized) {
      return;
    }

    Serial.print("DPS368 temp(C): ");
    Serial.print(temperatureC, 2);
    Serial.print(" | pressure(Pa): ");
    Serial.print(pressurePa, 2);
    Serial.print(" | altitude(m): ");
    Serial.println(altitudeM, 2);
  }

  inline void printSettings() {
    Serial.print("DPS368 settings: tempMr=");
    Serial.print(tempMr);
    Serial.print(" tempOsr=");
    Serial.print(tempOsr);
    Serial.print(" prsMr=");
    Serial.print(prsMr);
    Serial.print(" prsOsr=");
    Serial.print(prsOsr);
    Serial.print(" seaLevelPressure=");
    Serial.println(seaLevelPressureHpa, 2);
  }
}
