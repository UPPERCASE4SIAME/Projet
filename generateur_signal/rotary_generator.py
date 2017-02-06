#!/usr/bin/python
# coding: utf-8

"""
Autors : UPPERCASES / STRE / M2 SIAME / University Paul Sabatier
Projet : EmsBeanch
"""


from threading import Thread, Condition, Event
import RPi.GPIO as GPIO
import sys
import time
import pygame
from pygame import joystick

MAX    = 10000  # RPM
NORMAL = 1500
MIN    = 10



class Rotary_generatorPWM():
	PRIMARY_RPM   = 23 #output rotary primary 24
	SECONDARY_RPM = 24 #output rotary secondary 2
		
	def __init__(self, freq):		
		GPIO.setmode(GPIO.BCM)
		GPIO.setup(Rotary_generatorPWM.PRIMARY_RPM, GPIO.OUT)
		GPIO.setup(Rotary_generatorPWM.SECONDARY_RPM, GPIO.OUT)
		
		self.__pwm_primary = GPIO.PWM(Rotary_generatorPWM.PRIMARY_RPM, freq/60)
		self.__pwm_secondary = GPIO.PWM(Rotary_generatorPWM.SECONDARY_RPM, freq/60)
		
		self.__pwm_primary.start(0.3)
		self.__pwm_secondary.start(0.3)
		
	def update_freq(self, freq):
		print(freq/60)
		self.__pwm_primary.ChangeFrequency((freq*12)/60)
		self.__pwm_secondary.ChangeFrequency(freq/60)
		

class Gamepad(Thread):
	def __init__(self,callBack):
		Thread.__init__(self)
		self.__CallBack = callBack

	def __thruttle_up(self, x):
		""" translate x gamepad value to RPM value in speeding up"""
		thruttle = (MAX - NORMAL) * x
		thruttle = thruttle + NORMAL
		return thruttle
	
	def __thruttle_down(self, x):
		""" translate x gamepad value to RPM value in deceleration"""
		thruttle = (NORMAL - MIN) * ( x + 1)
		thruttle = thruttle + MIN
		return thruttle
		
			
	def run(self):
		pygame.init()
		jt = pygame.joystick.Joystick(0)
		jt.init()
		old_value = 0
		while True:
			for event in pygame.event.get():
				if (event.type == pygame.JOYBUTTONDOWN) and (event.button == 0):
					GPIO.cleanup()
					exit()
				elif (event.type == pygame.JOYAXISMOTION) and (event.axis == 2):
					if (abs(event.value - old_value) >= 0.02):
						old_value = event.value
						#Set value Rotary_generatorPWM
						
						if event.value == 0:
							"""power setting"""
							self.__CallBack(NORMAL)
							
						elif event.value > 0:
							"""thruttle down"""
							thruttle_down = self.__thruttle_down(-event.value) 
							self.__CallBack(thruttle_down)
							
						elif event.value > -1:
							"""thruttle up"""
							thruttle_up = self.__thruttle_up(-event.value) 
							self.__CallBack(thruttle_up)
							
						else:
							"""thruttle up"""
							self.__CallBack(MAX)
						

if __name__ =="__main__":
	print("Use the joystick to thruttle Up/Down.\nUse triangle to exit.") 
	rotary = Rotary_generatorPWM(NORMAL)
	gamepad = Gamepad(rotary.update_freq)
	gamepad.start()	

	
	
	
		

		
	
