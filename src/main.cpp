#include <baro.cpp>
#include <gps.cpp>
#include <imu.cpp>
#include <littlefs.cpp>
#include <rgb.cpp>

BARO DPS368;
GPS NEO_M9;
IMU ICM42688;
RGBLed led(24,22,23);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Boot: firmware starting");
    led.setColor(1.0f, 1.0f, 1.0f);
    DPS368.begin();
    ICM42688.begin();
    NEO_M9.begin();
}

void loop() {
    // NEO_M9.update();
    // NEO_M9.printReport();

    if (ICM42688.isInitialized()) {
        ICM42688.update();
        Serial.print("IMU: ");
        Serial.print(ICM42688.getAccX(), 3); Serial.print(",");
        Serial.print(ICM42688.getAccY(), 3); Serial.print(",");
        Serial.print(ICM42688.getAccZ(), 3); Serial.print(" |");
        Serial.print(ICM42688.getGyrX(), 3); Serial.print(",");
        Serial.print(ICM42688.getGyrY(), 3); Serial.print(",");
        Serial.print(ICM42688.getGyrZ(), 3); Serial.print(" |");
        Serial.println(ICM42688.getTemp(), 2);
    }

    if (DPS368.isConnected()) {
        DPS368.update();
        Serial.print("BARO: ");
        Serial.print(DPS368.getTemperatureC(), 2); Serial.print(" C | ");
        Serial.print(DPS368.getPressurePa(), 2); Serial.print(" Pa | ");
        Serial.print(DPS368.getAltitudeCm(), 2); Serial.println(" cm");
    }

    delay(10);
}