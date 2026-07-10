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
      char c = static_cast<char>(Serial1.read());
      Serial.print(c);
      gps.encode(c);
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