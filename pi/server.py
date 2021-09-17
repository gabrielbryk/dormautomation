#!/usr/bin/env python3
import serial
import time
from flask import Flask, request, jsonify, render_template
    
app = Flask(__name__)  
ser = None

@app.route("/")
def index():
    return render_template('control.html')

@app.route('/command',methods = ['POST'])
def command():
    content = request.json
    print(content)
    if('color' in content):
        msg = "color".ljust(10,'0') + content['color'] + "\n"
        ser.write(msg.encode())
        
    if('brightness' in content):
        msg = "brightness".ljust(10,'0') + content['brightness'] + "\n"
        ser.write(msg.encode())
    
    line = ser.readline().decode('utf-8').rstrip()
    print(line)

    return "fuck me"

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()
    app.run(debug = True,host="0.0.0.0")
