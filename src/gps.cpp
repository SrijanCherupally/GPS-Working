#include <Arduino.h>
#include <TinyGPSPlus.h>

class GPS {
private:
  TinyGPSPlus gps;

public:
  void begin() {
    Serial1.begin(38400);
    Serial.println("GPS running");
  }

  void update() {
    while (Serial1.available()) {
      gps.encode(Serial1.read());
    }
  }

  bool hasFix() const {
    return gps.location.isValid();
  }

  bool hasNewLocation() const {
    return gps.location.isUpdated();
  }

  double getLatitude() const {
    return gps.location.lat();
  }

  double getLongitude() const {
    return gps.location.lng();
  }

  double getAltitudeMeters() const {
    return gps.altitude.meters();
  }

  double getSpeedMps() const {
    return gps.speed.mps();
  }

  double getSpeedKmph() const {
    return gps.speed.kmph();
  }

  double getCourseDeg() const {
    return gps.course.deg();
  }

  int getSatellites() const {
    return gps.satellites.value();
  }

  void printReport() const {
    if (gps.location.isUpdated()) {
      Serial.print("Lat: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Lon: ");
      Serial.print(gps.location.lng(), 6);
      Serial.print(" Sats: ");
      Serial.print(gps.satellites.value());
      Serial.print(" Alt(m): ");
      Serial.print(gps.altitude.meters(), 2);
      Serial.print(" Speed(kph): ");
      Serial.println(gps.speed.kmph(), 2);
    }
  }
};