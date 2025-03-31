#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Servo.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

#define PIN_SERVO 5

Servo myservo;
Adafruit_BME280 bme;
volatile int H = 0;

void nowheight()
{
  H = bme.readAltitude(SEALEVELPRESSURE_HPA);
}

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Rocket System Starting..."));

  myservo.attach(PIN_SERVO);

  if (!bme.begin())
  {
    Serial.println("Starting BME280 failed!");
    while(1);
  }
  attachInterrupt(0, nowheight, CHANGE);
  Serial.println("System Ready!");
}

void loop()
{
  if (H >= 400)
  {
    Serial.println("Altitude reached 400m - Activating Servo");
    myservo.write(180);
    delay(1000);
    return;
  }
  
  Serial.print("Current Altitude: ");
  Serial.print(H);
  Serial.println(" m");
  delay(500);
}