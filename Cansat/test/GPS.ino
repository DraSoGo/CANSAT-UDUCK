#include <TinyGPS++.h>

HardwareSerial GPSserial(1);

#define RXPin 16
#define TXPin 17
#define GPSBaud 9600

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  GPSserial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
}

void loop()
{
  while (GPSserial.available())
  {
    gps.encode(GPSserial.read());
  }
  if (gps.location.isValid())
  {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("  Lon: ");
    Serial.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println("Location ERROR");
  }

  if (gps.time.isValid())
  {
    Serial.print("Time (HHMMSSCC): ");
    Serial.println(gps.time.value());
  }
  else
  {
    Serial.println("Time ERROR");
  }

  if (gps.speed.isValid())
  {
    Serial.print("Speed km/h: ");
    Serial.println(gps.speed.kmph());
  }
  else
  {
    Serial.println("Speed ERROR");
  }

  if (gps.course.isValid())
  {
    Serial.print("Course °: ");
    Serial.println(gps.course.deg());
  }
  else
  {
    Serial.println("Course ERROR");
  }

  if (gps.altitude.isValid())
  {
    Serial.print("Alt m: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Altitude ERROR");
  }

  if (gps.hdop.isValid())
  {
    Serial.print("HDOP: ");
    Serial.println(gps.hdop.value());
  }
  else
  {
    Serial.println("HDOP ERROR");
  }
  if (gps.satellites.isValid())
  {
    int sats = gps.satellites.value();
    Serial.print("Satellites: ");
    Serial.println(sats);
  }
  else
  {
    Serial.println("Satellites ERROR");
  }
  Serial.println("=============================");
  delay(1000);
}
