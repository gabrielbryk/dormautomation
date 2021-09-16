#!/bin/bash
cd arduino
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega led
