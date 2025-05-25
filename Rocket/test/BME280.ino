#include <Wire.h>
#include <MPU6050.h>

MPU6050 imu; // สร้างออบเจกต์ของ MPU6050

void setup() {
  Serial.begin(9600);
  Wire.begin();        // เริ่มใช้งาน I2C (A4 = SDA, A5 = SCL)
  imu.initialize();    // เริ่มต้น MPU6050

  // ตรวจสอบการเชื่อมต่อ
  if (!imu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1); // ค้างถ้าเชื่อมต่อไม่ได้
  }

  Serial.println("MPU6050 Initialized");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // อ่านค่าเซนเซอร์
  imu.getAcceleration(&ax, &ay, &az);
  imu.getRotation(&gx, &gy, &gz);

  // แปลงเป็นหน่วยจริง
  float ax_g = ax * 9.80665 / 16384.0;
  float ay_g = ay * 9.80665 / 16384.0;
  float az_g = az * 9.80665 / 16384.0;

  float gx_dps = gx / 131.0;
  float gy_dps = gy / 131.0;
  float gz_dps = gz / 131.0;

  // คำนวณ roll/pitch แบบง่าย
  float roll  = atan2(ay_g, az_g) * 180.0 / PI;
  float pitch = atan2(-ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;

  // พิมพ์ค่าออกทาง Serial Monitor
  Serial.print("Accel (g): ");
  Serial.print(ax_g, 2); Serial.print("\t");
  Serial.print(ay_g, 2); Serial.print("\t");
  Serial.print(az_g, 2); Serial.println();

  Serial.print("Gyro (°/s): ");
  Serial.print(gx_dps, 2); Serial.print("\t");
  Serial.print(gy_dps, 2); Serial.print("\t");
  Serial.print(gz_dps, 2); Serial.println();

  Serial.print("Roll: "); Serial.print(roll, 2);
  Serial.print("\tPitch: "); Serial.println(pitch, 2);

  Serial.println("----------------------");
  delay(500); // รอครึ่งวินาที
}
