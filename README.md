# **🦆 UDUCK-CANSAT 🦆**
## **🚀 Thailand CanSat-Rocket Competition 2025**

## **⚒️ Hardware**
1. **TTGO LoRa32 SX1276** : Controll,Communicated with ground
2. **MPU6050** : Sensor,Deployment
3. **GPS** : Sensor
4. **BME280** : Sensor
5. **Servo** : Deployment

## **💻  Software**
1. **Ardino IDE** : Write arduino for control hardware.
2. **CoolTerm** : See and save log from Arduino IDE.
3. **Visual Studio Code** : Analysis data from log.

## **🗃️ File**
1. **[❎]Blackbox** : Keep data on the board. 
2. **[✅]Cansat** : Code for cansat.

    - test : Code for test all tool in cansat.

        - BME280.ino : Code for test of BME280.
        - GPS.ino : Code for test of GPS.
        - GY-521.ino : Code for test of MPU6050.
        - TTGO.ino : Code for test of TTGO LoRa32 SX1276.
    - Cansat.ino : Code process in cansat.
3. **[✅]Circuit** : Reference picture about curcuit. 
4. **[✅]Ground** : Code for communicated on the ground.
    - Ground.ino : Code for communicated on the ground.
5. **[✅]Rocket** : Code for Rocket.

    - test : Code for test all tool in rocket.

        - BME280.ino : Code for test of BME280.
        - Servo.ino : Code for test of servo.
    - Rocket.ino : Code process in rocket.
6. **[⏬]libraries** : List libraries need to install before use this repo.
7. **[ℹ️]README.md** : Description of repo.
8. **[ℹ️]log1.txt** : Data from cansat.

|**✅ Ready to use**|**❎ Not ready to use**|
|---|---|
|**⏬ Need to install**|**ℹ️ Information**|

## **📃 Data Format**
|**Line**| **Part** | **Data** | **Unit** |
|---|---|---|---|
| 1|GPS| Latitude,Longitude | degree (°) |
| 2|GPS| Time | HHMMSSCC |
| 3|GPS| Course | degree (°) |
| 4|GPS| Speed | kilometer per hour (km/h) |
| 5|GPS| Altitude | meter (m) |
| 6|GPS| HDOP | unit |
| 7|GPS| Satellite | unit |
| 8|BME280| Temp | celsius (°C) |
| 9|BME280| Pressure | hectopascal (hPa) |
| 10|BME280| Altitude | meter (m) |
| 11|BME280| Humidity | percent (%) |
| 12|MPU6050| Accel (x,y,z) | meter per second² (m/s²) |
| 13|MPU6050| Gyro (x,y,z) | degrees per second (°/s) |
| 14|MPU6050| roll,pitch | degree (°) |