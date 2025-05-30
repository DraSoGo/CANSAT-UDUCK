#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TinyGPS++.h>
#include <MPU6050.h>
// #include <LittleFS.h>

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
// #define BAND 921925000
#define BAND 922525000
#define LORA_BW 125E3
#define LORA_SF 9

// ——— I²C for BME280 & MPU6050 ———
#define I2C_SDA 21
#define I2C_SCL 22
#define SEALEVELPRESSURE_HPA 1013.25

Adafruit_BME280 bme; // BME280 sensor
MPU6050 imu;         // MPU6050 IMU

// Raw sensor readings & computed angles
int16_t ax, ay, az, gx, gy, gz;
double roll, pitch;

bool chbme = 0,chmpu = 0;

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
    while (1)
      ;
  }
  LoRa.setSignalBandwidth(LORA_BW);
  LoRa.setSpreadingFactor(LORA_SF);
  // LoRa.setSyncWord(0x6D);
  // —— I2C bus setup ——
  Wire.begin(I2C_SDA, I2C_SCL);
  imu.initialize();
}

void loop()
{
  // start a new LoRa packet
  if(!chbme)
  {
    if(bme.begin(0x76))
    {
      chbme = 1;
    }
  }
  if(!chmpu)
  {
    if(imu.testConnection())
    {
      chmpu = 1;
    }
  }
  LoRa.beginPacket();
  printGPS();
  if(chbme)
  {
    printBME();
  }
  if(chmpu)
  {
    printGY();
  }
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
  if (gps.location.isValid())
  {
    LoRa.print(gps.location.lat(), 6);
    LoRa.print(",");
    LoRa.println(gps.location.lng(), 6);
  }
  else
  {
    LoRa.println("-");
  }
  gps.time.isValid()?LoRa.println(gps.time.value()):LoRa.println("-");
  gps.speed.isValid()?LoRa.println(gps.speed.value()):LoRa.println("-");
  gps.course.isValid()?LoRa.println(gps.course.value()):LoRa.println("-");
  gps.altitude.isValid()?LoRa.println(gps.altitude.value()):LoRa.println("-");
  gps.hdop.isValid()?LoRa.println(gps.hdop.value()):LoRa.println("-");
  gps.satellites.isValid()?LoRa.println(gps.satellites.value()):LoRa.println("-");
  LoRa.println();
}

// ——— Print BME280 data over Serial ———
void printBME()
{
  LoRa.println(bme.readTemperature());
  LoRa.println(bme.readPressure() / 100.0F);
  LoRa.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
  LoRa.println(bme.readHumidity());
  LoRa.println();
}

// ——— Print MPU6050 (accel + gyro + angles) ———
void printGY()
{
  imu.getAcceleration(&ax, &ay, &az);
  imu.getRotation(&gx, &gy, &gz);
  if(ax == 0 && ay == 0 && az == 0 && gx == 0 && gy == 0 && gz == 0)
  {
    ESP.restart();
  }
  // accel
  LoRa.print(ax * (9.80665 / 16384.0));
  LoRa.print(",");
  LoRa.print(ay * (9.80665 / 16384.0));
  LoRa.print(",");
  LoRa.println(az * (9.80665 / 16384.0));

  // gyro
  LoRa.print(gx / 131.0);
  LoRa.print(",");
  LoRa.print(gy / 131.0);
  LoRa.print(",");
  LoRa.println(gz / 131.0);

  // compute roll & pitch
  roll = atan2(ay, az) * 180.0 / PI;
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  LoRa.print(roll);
  LoRa.print(",");
  LoRa.println(pitch);
  LoRa.println();
}
