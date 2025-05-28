#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

MPU6050 imu;
bool ch = 0,chs = 0,chh = 0;
int16_t axRaw, ayRaw, azRaw;
int16_t gxRaw, gyRaw, gzRaw;
double ax, ay, az, gx, gy, gz, roll, pitch, froll, fpitch;
#define PIN_SERVO 9
Servo myservo;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  myservo.attach(PIN_SERVO);
  imu.initialize();
  if (!imu.testConnection())
  {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 Initialized");
}

void loop()
{
  imu.getAcceleration(&axRaw, &ayRaw, &azRaw);
  imu.getRotation(&gxRaw, &gyRaw, &gzRaw);
  if(!chs)
  {
    myservo.write(20);
    chs = 1;
    delay(10000);
  }
  // delay(600000);
  ax = axRaw * (9.80665 / 16384.0);
  ay = ayRaw * (9.80665 / 16384.0);
  az = azRaw * (9.80665 / 16384.0);
  gx = gxRaw / 131.0;
  gy = gyRaw / 131.0;
  gz = gzRaw / 131.0;
  // printAccel();
  // printGyro();
  printRollPitch();
  if (!chh)
  {
    chh = 1;
    froll = roll;
    fpitch = pitch;
  }
  if(abs(abs(roll)-abs(froll)) >= 45 || abs(pitch)-abs(fpitch) >= 45)
  {
    Serial.println("Return");
    if(!ch)
    {
      ch = 1;
      Serial.println("Run Servo");
      for (int pos = 20; pos <= 100; pos += 1)
      {
        myservo.write(pos);
        delay(15);
      }
      myservo.detach();
      // delay(5000);
      // return;
    }
    // myservo.write(0);
  }
  Serial.println("---------");
  delay(100);
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
