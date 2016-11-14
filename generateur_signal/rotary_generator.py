#!/usr/bin/python

import RPi.GPIO as GPIO
import time

LATENCE = 0.01
#LATENCE = 0.01295

rotary_24 = 23 #sortie rotary encodeur 24
rotary_2 = 24 #sortie rotary encodeur 2

GPIO.setmode(GPIO.BCM)

GPIO.setup(rotary_24, GPIO.OUT)
GPIO.setup(rotary_2, GPIO.OUT)

compteur = 0

while True:
    if compteur % 2 == 0:
	GPIO.output(rotary_24, GPIO.HIGH)
    else:
	GPIO.output(rotary_24, GPIO.LOW)

    if compteur == 24/2:
	GPIO.output(rotary_2, GPIO.HIGH)
    else:
	GPIO.output(rotary_2, GPIO.LOW)
    compteur = compteur + 1
    compteur = compteur % 24

    time.sleep(LATENCE)
