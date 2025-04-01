#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>

//Lora
#define  LoRa_SCK   13
#define  LoRa_MISO  12
#define  LoRa_MOSI  11
#define  LoRa_CS    10
#define  LoRa_RST   9
#define  DI0        2
#define  BAND    915E6
#define  Select    LOW   //  Low CS means that SPI device Selected
#define  DeSelect  HIGH  //  High CS means that SPI device Deselected

//GPS
#define RXPin 4
#define TXPin 3
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

//BME280
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

//GY-521
MPU6050 imu;
int16_t ax, ay, az, gx, gy, gz;
double roll, pitch;

void setup()
{
  Serial.begin(9600);
  //Lora setup
  while (!Serial);
  pinMode(LoRa_CS, OUTPUT);
  digitalWrite(LoRa_CS, DeSelect);
  SPI.begin();
  LoRa.setPins( LoRa_CS, LoRa_RST, DI0 );
  digitalWrite(LoRa_CS, Select);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
  }
  else
  {
    Serial.println("LoRa Initial OK!");
    delay(1000);
  }

  //GPS setup
  ss.begin(GPSBaud);

  //BME280 setup
  bool status;
  status = bme.begin();
  if (!status) {
    Serial.println("Starting BME280 failed!");
    while (1);
  }
  
  Serial.println("BME280 Initial OK!");
  Serial.println();
  //GY-521 setup
  Wire.begin();
  imu.initialize();
  if (!imu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 Initialized OK!");
}

void loop()
{
  LoRa.beginPacket();
  if(ss.available() > 0)
  {
    LoRa.println("Data GPS");
    printGPS();
  }
  LoRa.println("Data BME280");
  printBME();
  LoRa.println("Data GY-521");
  printGY();
  LoRa.endPacket();
  delay(1000);
}

//GPS print
void printGPS()
{
  while (ss.available())
  {
    gps.encode(ss.read());
  }
  // gps.encode(ss.read());
  //Location
  if (gps.location.isValid())
  {
    // Latitude in degrees (double)
    LoRa.print("Latitude = ");
    LoRa.print(gps.location.lat(), 6);
    // Longitude in degrees (double)
    LoRa.print(" Longitude = ");
    LoRa.println(gps.location.lng(), 6);
  }
  else
  {
    LoRa.println("Location ERROR!");
  }

  //Time
  if(gps.time.isValid())
  {
    // Raw time in HHMMSSCC format (u32)
    LoRa.print("Raw time in HHMMSSCC = ");
    LoRa.println(gps.time.value());
  }
  else
  {
    LoRa.println("Time ERROR!");
  }

  //Speed
  if(gps.speed.isValid())
  {
    // Speed in kilometers per hour (double)
    LoRa.print("Speed in km/h = ");
    LoRa.println(gps.speed.kmph());
  }
  else
  {
    LoRa.println("Speed ERROR!");
  }

  //Direction
  if(gps.course.isValid())
  {
    // Direction in degrees (double)
    LoRa.print("Direction in degrees = ");
    LoRa.println(gps.course.deg());
  }
  else
  {
    LoRa.println("Direction ERROR!");
  }

  //Altitude
  if(gps.altitude.isValid())
  {
    // Altitude in meters (double)
    LoRa.print("Altitude in meters = ");
    LoRa.println(gps.altitude.meters());
  }
  else
  {
    LoRa.println("Altitude ERROR!");
  }

  //HDOP
  if(gps.hdop.isValid())
  {
    // ความแม่นยำ
    LoRa.print("HDOP = ");
    LoRa.println(gps.hdop.value());
  }
  else
  {
    LoRa.println("HDOP ERROR!");
  }

}

//BME280 print
void printBME()
{
  //temp
  LoRa.print("Temperature = ");
  LoRa.print(bme.readTemperature());
  LoRa.println(" *C");
  
  //pressure
  LoRa.print("Pressure = ");
  LoRa.print(bme.readPressure() / 100.0F);
  LoRa.println(" hPa");
  
  //Altitude
  LoRa.print("Altitude = ");
  LoRa.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  LoRa.println(" m");
  
  //Humidity
  LoRa.print("Humidity = ");
  LoRa.print(bme.readHumidity());
  LoRa.println(" %");
  
  LoRa.println();
}

//GY-521 print
void printGY()
{
  imu.getAcceleration(&ax, &ay, &az);
  imu.getRotation(&gx, &gy, &gz);
  printAccel();
  printGyro();
  printRollPitch();
}

void printAccel()
{
  LoRa.print("Accel = ");
  LoRa.print(ax); LoRa.print("\t");
  LoRa.print(ay); LoRa.print("\t");
  LoRa.print(az); LoRa.println();
}

void printGyro()
{
  LoRa.print("Gyro = ");
  LoRa.print(gx); LoRa.print("\t");
  LoRa.print(gy); LoRa.print("\t");
  LoRa.print(gz); LoRa.println();
}

void printRollPitch()
{
  roll = atan2(ay, az) * 180.0 / PI;
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  LoRa.print("Roll/Pitch = ");
  LoRa.print(pitch); LoRa.print("\t");
  LoRa.print(roll); LoRa.println();
}