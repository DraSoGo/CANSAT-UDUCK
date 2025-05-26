import serial
import time
from datetime import datetime

ser = serial.Serial('/dev/ttyACM0', 9600)

with open("log.txt", "w") as f:
    while True:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if line == "-------------":
            now = datetime.now()
            timestamp = now.strftime("%Y-%m-%d %H:%M:%S")
            f.write(timestamp + "\n")
            print(timestamp)
        print(line)
        f.write(line + "\n")
