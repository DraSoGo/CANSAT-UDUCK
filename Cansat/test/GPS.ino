#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RXPin 4
#define TXPin 3

static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      // Latitude in degrees (double)
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      // Longitude in degrees (double)
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);

      // Raw time in HHMMSSCC format (u32)
      Serial.print("Raw time in HHMMSSCC = ");
      Serial.println(gps.time.value());

      // Speed in kilometers per hour (double)
      Serial.print("Speed in km/h = ");
      Serial.println(gps.speed.kmph());

      // Direction in degrees (double)
      Serial.print("Direction in degrees = ");
      Serial.println(gps.course.deg());

      // Altitude in meters (double)
      Serial.print("Altitude in meters = ");
      Serial.println(gps.altitude.meters());

      // ความแม่นยำ
      Serial.print("HDOP = ");
      Serial.println(gps.hdop.value());
    }
  }
}