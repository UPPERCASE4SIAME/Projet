#!/usr/bin/python
# coding: utf-8

"""
Autors : UPPERCASES / STRE / M2 SIAME / University Paul Sabatier
Projet : EmsBeanch generateur de signal 
"""


from threading import Thread, Condition, Event
import RPi.GPIO as GPIO
import sys
import time
import pygame
from pygame import joystick

MAX    = 10000  # RPM 
NORMAL = 500	
MIN    = 50

class Rotary_generator(Thread):
	PRIMARY_RPM   = 23 #output rotary primary 24 on  GPIO 23
	SECONDARY_RPM = 24 #output rotary secondary 2 on GPIO 24
		
	def __init__(self, rpm):
		Thread.__init__(self)
		GPIO.setmode(GPIO.BCM)
		GPIO.setup(Rotary_generator.PRIMARY_RPM, GPIO.OUT)
		GPIO.setup(Rotary_generator.SECONDARY_RPM, GPIO.OUT)
		self.__keep_running = Event()
		self.__keep_running.set()
		self.update_RPM(rpm)
		self.__count = 0
		
	def run (self):
		while self.__keep_running.isSet():
			if self.__count % 2 != 0:
				GPIO.output(Rotary_generator.PRIMARY_RPM, GPIO.HIGH)
			else:
				GPIO.output(Rotary_generator.PRIMARY_RPM, GPIO.LOW)

			if self.__count == 24/2:
				GPIO.output(Rotary_generator.SECONDARY_RPM, GPIO.HIGH)
			else:
				GPIO.output(Rotary_generator.SECONDARY_RPM, GPIO.LOW)
				
			self.__count = self.__count + 1
			self.__count = self.__count % 24

			time.sleep(self.__LATENCE)
	
	def update_RPM(self, rpm):
		self.__LATENCE = 1.7/rpm
		print(self.__LATENCE)	
	
	def stop (self):
		self.__keep_running.clear()
		

class Gamepad(Thread):
	def __init__(self,rotary):
		Thread.__init__(self)
		self.__CallBack = rotary.update_RPM

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
			# Attente passive
			event = pygame.event.wait() 
			
			if (event.type == pygame.JOYBUTTONDOWN) and (event.button == 9):
				rotary.stop()
				GPIO.cleanup()	
				print("exit")
				exit()
				
			elif (event.type == pygame.JOYAXISMOTION) and (event.axis == 2):
				#print(event.value)
				if (abs(event.value - old_value) >= 0.05):
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
	print("Use the joystick to thruttle Up/Down.\nUse START to exit.") 
	rotary = Rotary_generator(NORMAL)
	rotary.start()
	gamepad = Gamepad(rotary)
	gamepad.start()	

	
	
	
		

		
	
