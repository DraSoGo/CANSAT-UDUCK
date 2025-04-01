#include <Wire.h>
#include <MPU6050.h>

MPU6050 imu;
double ax, ay, az, gx, gy, gz, roll, pitch;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  imu.initialize();
  
  if (!imu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  Serial.println("MPU6050 Initialized");
}

void loop()
{
  imu.getAcceleration(&ax, &ay, &az);
  imu.getRotation(&gx, &gy, &gz);
  printAccel();
  printGyro();
  printRollPitch();
  
  delay(10);
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
  Serial.print(pitch); Serial.print("\t");
  Serial.print(roll); Serial.println();
}
