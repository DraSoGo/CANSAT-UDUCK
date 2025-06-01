# **🦆 UDUCK-CANSAT 🦆**
## **🚀 Thailand CanSat-Rocket Competition 2025**

## **👨‍🔧 Team**

<img src="https://raw.githubusercontent.com/DraSoGo/CANSAT-UDUCK/refs/heads/main/Source/UDUCK_team.jpg"/>

## **🏆 Trophy**

<!-- ![image]() -->

<img src="https://raw.githubusercontent.com/DraSoGo/CANSAT-UDUCK/refs/heads/main/Source/Trophy.jpeg" width="200"/>

**Best Technique Award**

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
4. **[✅]Data** : Read log and analysis data. 
    - Data_analysis_1.ipynb : Code for analysis data from log_1.txt.
    - Data_analysis_2.ipynb : Code for analysis data from log_2.txt.
    - Data_analysis_3.ipynb : Code for analysis data from log_13_UDUCK.txt.
    - log_1.txt : Data from antenna 1.
    - log_2.txt : Data from antenna 2.
    - log_13_UDUCK.txt : Data from ground station of director.
    - log_testtemp.txt : Data from thermal test.
    - loglora.txt : Data from test distance of lora.
    - logtesthigh.txt : Data from something(IDK I forget it haha).
    - logteswind.txt : Data from test in Tunnel wind.
    - Read_Serial_1.py : Read data from antenna 1.
    - Read_Serial_2.py : Read data from antenna 2.
    - sdf_l_output.xlsx : Data in excel.
5. **[✅]Ground** : Code for communicated on the ground.
    - Ground.ino : Code for communicated on the ground.
6. **[✅]Rocket** : Code for Rocket.

    - test : Code for test all tool in rocket.

        - BME280.ino : Code for test of BME280.
        - Servo.ino : Code for test of servo.
    - Rocket.ino : Code process in rocket.
7. **[⏬]libraries** : List libraries need to install before use this repo.
8. **[ℹ️]Slide** : Slide presentation.
    - Presentation_After.pdf : Slide presentation after launch rocket.
    - Presentation_Before.pdf : Slide presentation before launch rocket.
9. **[ℹ️]Source** : Picture in repo.
    - Trophy.jpeg : Picture trophy.
    - UDUCK_team.jpg : Picture of my team.
10. **[ℹ️]README.md** : Description of repo.

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