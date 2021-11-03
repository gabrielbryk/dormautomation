
#!/usr/bin/env python3
import keyboard
import requests
import json
import time

def send(payload):
    try:
        response = requests.request("POST", url, headers=headers, data=payload, timeout=0.0000000001)
    except requests.exceptions.ReadTimeout: 
        pass


def color(c):
    print(c)
    payload = json.dumps({
        "color": c
    })
    send(payload)
    

   # print(response.text)

def routine(c):
    print(c)
    payload = json.dumps({
        "routine": c
    })
    send(payload)


def key_press(key):
    k=key.name
    #First row colors
    if k=='q':  
        color("white")
    elif k=='w': 
        color("chill")
    elif k=='e': 
        color("piss")
    elif k=='r': 
        color("sex")
    elif k=='t': 
        color("orange")
    elif k=='y': 
        color("teal")
    #Second Row  routine
    elif k=='a': 
        routine("default")
    elif k=='s': 
        routine("movie")
    elif k=='d': 
        routine("orange")
    elif k=='f': 
        routine("teal")



print("Starting Keyboard control of lights")
url = "http://localhost:5000/command"
headers = {
  'Content-Type': 'application/json'
}
payload=""

keyboard.on_press(key_press)

while True:
    time.sleep(1)

