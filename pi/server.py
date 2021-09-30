
#!/usr/bin/env python3
import serial
import time
import json
from flask import Flask, request, jsonify, render_template
    
app = Flask(__name__)  
ser = None

def normalize(num):
    if(num>100):
        num=100
    return (255-0)*((num-0)/(100-0))+0

@app.route("/")
def index():
    return render_template('control.html')

@app.route('/command',methods = ['POST'])
def command():
    content = request.json
    print(json.dumps(content))
    if('color' in content):
        msg = "color".ljust(10,'0') + content['color'] + "\n"
        ser.write(msg.encode())

        
    if('brightness' in content):
        msg = "brightness".ljust(10,'0') + str(normalize(int(content['brightness']))) + "\n"
        ser.write(msg.encode())


    if('on' in content):
        msg = "on".ljust(10,'0') + content['on'] + "\n"
        ser.write(msg.encode())

    if('off' in content):
            msg = "off".ljust(10,'0') + content['off'] + "\n"
            ser.write(msg.encode())

    line = ser.readline().decode('utf-8').rstrip()
    print(line)

    return "fuck me"

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=3)
    ser.flush()
    app.run(debug = True,host="0.0.0.0")
