# **🦆 UDUCK-CANSAT 🦆**
## **🚀 Thailand CanSat-Rocket Competition 2025**
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
6. **[⏬]libraries** : list libraries need to install before use this repo.
7. **[ℹ️]README.md** : description of repo.
8. **[ℹ️]log1.txt** : data from cansat.

## **⚒️ Tool**
1. **TTGO LoRa32 SX1276** : controll,communicated with ground
2. **MPU6050** : sensor,deployment
3. **GPS** : sensor
4. **BME280** : sensor
5. **Servo** : deployment

|**✅ Ready to use**|**❎ Not ready to use**|
|---|---|
|**⏬ Need to install**|**ℹ️ Information**|
## **📃 Data Format**
|**Line**| **Part** | **Data** | **Unit** |
|---|---|---|---|
| 1|GPS| Latitude,Longitude | degree (°) |
| 2|GPS| Time | HHMMSSCC |
| 3|GPS| Speed | kilometer per hour (km/h) |
| 4|GPS| Altitude | meter (m) |
| 5|GPS| HDOP | unit |
| 6|GPS| Satellite | unit |
| 7|BME280| Temp | celsius (°C) |
| 8|BME280| Pressure | hectopascal (hPa) |
| 9|BME280| Altitude | meter (m) |
| 10|BME280| Humidity | percent (%) |
| 11|MPU6050| Accel (x,y,z) | meter per second² (m/s²) |
| 12|MPU6050| Gyro (x,y,z) | degrees per second (°/s) |
| 13|MPU6050| rool,pitch | degree (°) |