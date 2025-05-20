# **UDUCK-CANSAT**
## **to Thailand CanSat-Rocket Competition 2025**
## **Tool**
1. **TTGO LoRa32 SX1276** : controll,communicated with ground
2. **MPU6050** : sensor,deployment
3. **GPS** : sensor
4. **BME280** : sensor
5. **Servo** : deployment
## **Data Format**
|**Line**| **Part** | **Data** | **Unit** |
|---|---|---|---|
| 1| GPS | Latitude,Longitude | degree (°) |
| 2|   | Time | HHMMSSCC |
| 3|   | Speed | kilometer per hour (km/h) |
| 4|   | Altitude | meter (m) |
| 5|   | HDOP | unit |
| 6|   | Satellite | unit |
| 7|BME280| Temp | celsius (°C) |
| 8| | Pressure | hectopascal (hPa) |
| 9|   | Altitude | meter (m) |
| 10| | Humidity | percent (%) |
| 11| MPU6050 | Accel (x,y,z) | meter per second² (m/s²) |
| 12|  | Gyro (x,y,z) | degrees per second (°/s) |
| 13|  | rool,pitch | degree (°) |