#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TinyGPS++.h>
#include <MPU6050.h>

// ——— GPS over UART1 ———
HardwareSerial GPSserial(1);
#define RXPin 16 // GPIO16 (RX1)
#define TXPin 17 // GPIO17 (TX1)
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

// ——— LoRa SPI pins (TTGO LoRa32 V1) ———
#define LORA_SCK 5
#define LORA_MISO 19
#define LORA_MOSI 27
#define LORA_SS 18
#define LORA_RST 14
#define LORA_DIO0 26
#define BAND 915E6

// ——— I²C for BME280 & MPU6050 ———
#define I2C_SDA 21
#define I2C_SCL 22
#define SEALEVELPRESSURE_HPA 1013.25

Adafruit_BME280 bme; // BME280 sensor
MPU6050 imu;         // MPU6050 IMU

// Raw sensor readings & computed angles
int16_t ax, ay, az, gx, gy, gz;
double roll, pitch;

void setup()
{
  // Serial for debug
  Serial.begin(115200);
  while (!Serial)
    ;

  // —— GPS UART setup ——
  GPSserial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

  // —— LoRa setup ——
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(BAND))
  {
    Serial.println("LoRa init failed!");
    while (1)
      ;
  }
  Serial.println("LoRa Initialized OK");
  LoRa.setSyncWord(0x6D);
  // —— I2C bus setup ——
  Wire.begin(I2C_SDA, I2C_SCL);

  // —— BME280 init ——
  if (!bme.begin(0x76))
  {
    Serial.println("BME280 init failed!");
    while (1)
      ;
  }
  Serial.println("BME280 Initialized OK");

  // —— MPU6050 init ——
  imu.initialize();
  if (!imu.testConnection())
  {
    Serial.println("MPU6050 connection failed!");
    while (1)
      ;
  }
  Serial.println("MPU6050 Initialized OK");
}

void loop()
{
  // start a new LoRa packet
  LoRa.beginPacket();

  // GPS data
  printGPS();

  // BME280 data
  printBME();

  // IMU data
  printGY();

  // finish and send
  LoRa.endPacket();

  delay(1000);
}

// ——— Print GPS data over LoRa ———
void printGPS()
{
  // feed GPS characters
  while (GPSserial.available())
  {
    gps.encode(GPSserial.read());
  }

  Serial.println("-- GPS --");
  LoRa.println("-- GPS --");

  if (gps.location.isValid())
  {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("  Lon: ");
    Serial.println(gps.location.lng(), 6);
    LoRa.print("Lat: ");
    LoRa.print(gps.location.lat(), 6);
    LoRa.print("  Lon: ");
    LoRa.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println("Location ERROR");
    LoRa.println("Location ERROR");
  }

  if (gps.time.isValid())
  {
    Serial.print("Time (HHMMSSCC): ");
    Serial.println(gps.time.value());
    LoRa.print("Time (HHMMSSCC): ");
    LoRa.println(gps.time.value());
  }
  else
  {
    Serial.println("Time ERROR");
    LoRa.println("Time ERROR");
  }

  if (gps.speed.isValid())
  {
    Serial.print("Speed km/h: ");
    Serial.println(gps.speed.kmph());
    LoRa.print("Speed km/h: ");
    LoRa.println(gps.speed.kmph());
  }
  else
  {
    Serial.println("Speed ERROR");
    LoRa.println("Speed ERROR");
  }

  if (gps.course.isValid())
  {
    Serial.print("Course °: ");
    Serial.println(gps.course.deg());
    LoRa.print("Course °: ");
    LoRa.println(gps.course.deg());
  }
  else
  {
    Serial.println("Course ERROR");
    LoRa.println("Course ERROR");
  }

  if (gps.altitude.isValid())
  {
    Serial.print("Alt m: ");
    Serial.println(gps.altitude.meters());
    LoRa.print("Alt m: ");
    LoRa.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Altitude ERROR");
    LoRa.println("Altitude ERROR");
  }

  if (gps.hdop.isValid())
  {
    Serial.print("HDOP: ");
    Serial.println(gps.hdop.value());
    LoRa.print("HDOP: ");
    LoRa.println(gps.hdop.value());
  }
  else
  {
    Serial.println("HDOP ERROR");
    LoRa.println("HDOP ERROR");
  }
  if (gps.satellites.isValid())
  {
    int sats = gps.satellites.value();
    Serial.print("Satellites: ");
    Serial.println(sats);
    LoRa.print("Satellites: ");
    LoRa.println(sats);
  }
  else
  {
    Serial.println("Satellites ERROR");
    LoRa.println("Satellites ERROR");
  }

  Serial.println();
  LoRa.println();
}

// ——— Print BME280 data over Serial ———
void printBME()
{
  Serial.println("-- BME280 --");
  Serial.print("Temp °C: ");
  Serial.println(bme.readTemperature());
  Serial.print("Pressure hPa: ");
  Serial.println(bme.readPressure() / 100.0F);
  Serial.print("Alt m: ");
  Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print("Humidity %: ");
  Serial.println(bme.readHumidity());
  Serial.println();
  LoRa.println("-- BME280 --");
  LoRa.print("Temp °C: ");
  LoRa.println(bme.readTemperature());
  LoRa.print("Pressure hPa: ");
  LoRa.println(bme.readPressure() / 100.0F);
  LoRa.print("Alt m: ");
  LoRa.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
  LoRa.print("Humidity %: ");
  LoRa.println(bme.readHumidity());
  LoRa.println();
}

// ——— Print MPU6050 (accel + gyro + angles) ———
void printGY()
{
  imu.getAcceleration(&ax, &ay, &az);
  imu.getRotation(&gx, &gy, &gz);

  // accel
  Serial.print("Accel X,Y,Z: ");
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.println(az);
  LoRa.print("Accel X,Y,Z: ");
  LoRa.print(ax);
  LoRa.print(", ");
  LoRa.print(ay);
  LoRa.print(", ");
  LoRa.println(az);

  // gyro
  Serial.print("Gyro X,Y,Z:  ");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.println(gz);
  LoRa.print("Gyro X,Y,Z:  ");
  LoRa.print(gx);
  LoRa.print(", ");
  LoRa.print(gy);
  LoRa.print(", ");
  LoRa.println(gz);

  // compute roll & pitch
  roll = atan2(ay, az) * 180.0 / PI;
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  Serial.print("Roll °: ");
  Serial.print(roll);
  Serial.print("  Pitch °: ");
  Serial.println(pitch);

  Serial.println();
  LoRa.print("Roll °: ");
  LoRa.print(roll);
  LoRa.print("  Pitch °: ");
  LoRa.println(pitch);

  LoRa.println();
}
