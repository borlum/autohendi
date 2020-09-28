import serial
import struct
import time
import datetime

import pandas as pd

# Open serial connection
try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
except Exception as e:
    print("Failed to open serial conn...")


# DataFrame for storage
df = pd.DataFrame(columns=["t", "P", "T"])

i = 0

while i < 5:
    out = 2000.0

    # Serial read/write
    ser.write(str(out).encode())
    #P = float(ser.readline().decode("utf-8").strip("\r\n"))
    
    #df.loc[i] = [
    #    datetime.datetime.now().replace(microsecond=0).isoformat(),
    #    P, 22.0
    #]

    #print(df)
    
    # Sample time
    i += 1
    time.sleep(15)