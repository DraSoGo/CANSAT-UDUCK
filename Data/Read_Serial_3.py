import serial
import time
from datetime import datetime

ser = serial.Serial('/dev/ttyACM1', 9600)

with open("log_3.txt", "w") as f:
    while True:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if line == "-------------":
            now = datetime.now()
            timestamp = now.strftime("%Y-%m-%d %H:%M:%S")
            f.write(timestamp + "\n")
            print(timestamp)
        print(line)
        f.write(line + "\n")