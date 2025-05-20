# **🦆 UDUCK-CANSAT 🦆**
## **🚀 Thailand CanSat-Rocket Competition 2025**
## **⚒️ Tool**
1. **TTGO LoRa32 SX1276** : controll,communicated with ground
2. **MPU6050** : sensor,deployment
3. **GPS** : sensor
4. **BME280** : sensor
5. **Servo** : deployment
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