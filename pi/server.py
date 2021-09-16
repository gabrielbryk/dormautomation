#!/usr/bin/env python3
import serial
import time
from flask import Flask

app = Flask(__name__)  
ser = None

@app.route("/")
def index():
    return "fuck"
    
@app.route('/color/<color>')
def color(color):
    msg = "color"+str(color)+"\n"
    ser.write(msg.encode())
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    return "fuck me"

@app.route('/piss')
def piss():
    msg = "color5\n"
    ser.write(msg.encode())
    line = ser.readline().decode('utf-8').rstrip()
    print(line)
    return "fuck me"

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()
    app.run(debug = True)
