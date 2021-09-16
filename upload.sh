#!/bin/bash
cd arduino
arduino-cli compile -v --fqbn arduino:avr:mega led
arduino-cli upload -v -p /dev/ttyACM0 --fqbn arduino:avr:mega led
