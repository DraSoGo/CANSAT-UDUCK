#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 imu;
bool ch = 0;
double first = 500;
int16_t axRaw, ayRaw, azRaw;
int16_t gxRaw, gyRaw, gzRaw;
double ax, ay, az, gx, gy, gz, roll, pitch;
#define PIN_SERVO 9
Servo myservo;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  myservo.attach(PIN_SERVO);
  imu.initialize();
  if (!imu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 Initialized");
}

void loop()
{
  imu.getAcceleration(&axRaw, &ayRaw, &azRaw);
  imu.getRotation(&gxRaw, &gyRaw, &gzRaw);
  ax = axRaw * (9.80665 / 16384.0);
  ay = ayRaw * (9.80665 / 16384.0);
  az = azRaw * (9.80665 / 16384.0);
  gx = gxRaw / 131.0;
  gy = gyRaw / 131.0;
  gz = gzRaw / 131.0;
  printAccel();
  printGyro();
  printRollPitch();
  if(first == 500)
  {
    first = roll;
  }
  Serial.println(first);
  if(first/abs(first) != roll/abs(roll))
  {
    Serial.println("Return");
    if(!ch)
    {
      ch = 1;
      Serial.println("Run Servo");
      myservo.write(180);
      // delay(1000);
      // myservo.detach();
    }
    // myservo.write(0);
  }
  Serial.println("---------");
  delay(1000);
}

void printAccel()
{
  Serial.print("Accel: ");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.println();
}

void printGyro()
{
  Serial.print("Gyro: ");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.println();
}

void printRollPitch()
{
  roll = atan2(ay, az) * 180.0 / PI;
  pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  Serial.print("Roll/Pitch: ");
  Serial.print(roll); Serial.print("\t");
  Serial.print(pitch); Serial.println();
}
