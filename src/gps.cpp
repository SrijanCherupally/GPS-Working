#include <Arduino.h>
#include <TinyGPSPlus.h>

class GPS {
private:
  TinyGPSPlus gps;

public:
  void begin() {
    Serial1.begin(38400);
    Serial.println("GPS running at 38400");
  }

  void update() {
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }
}

  bool hasFix() {
    return gps.location.isValid();
  }

  bool hasNewLocation() {
    return gps.location.isUpdated();
  }

  double getLatitude() {
    return gps.location.lat();
  }

  double getLongitude() {
    return gps.location.lng();
  }

  double getAltitudeMeters() {
    return gps.altitude.meters();
  }

  double getSpeedMps() {
    return gps.speed.mps();
  }

  double getSpeedKmph() {
    return gps.speed.kmph();
  }

  double getCourseDeg() {
    return gps.course.deg();
  }

  int getSatellites() {
    return gps.satellites.value();
  }

  void printReport() {
    Serial.println("\n========== GPS ==========");

    Serial.print("Fix        : ");
    Serial.println(gps.location.isValid() ? "YES" : "NO");

    Serial.print("Satellites : ");
    Serial.println(gps.satellites.value());

    if (gps.location.isValid()) {
        Serial.print("Latitude   : ");
        Serial.println(gps.location.lat(), 6);

        Serial.print("Longitude  : ");
        Serial.println(gps.location.lng(), 6);

        Serial.print("Altitude   : ");
        Serial.print(gps.altitude.meters(), 2);
        Serial.println(" m");

        Serial.print("Speed      : ");
        Serial.print(gps.speed.kmph(), 2);
        Serial.println(" km/h");

        Serial.print("Heading    : ");
        Serial.print(gps.course.deg(), 1);
        Serial.println(" deg");
    }

    Serial.println("=========================\n");
}
};