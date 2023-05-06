import serial
import pygame


pygame.mixer.init()

basketball_sound = pygame.mixer.Sound("basketball_shot.wav")


arduino_port = "/dev/tty.usbmodem11101"
arduino_baudrate = 9600


ser = serial.Serial(arduino_port, arduino_baudrate)

try:
    while True:
        signal = ser.read(1)
        if signal == b'\x01':
            basketball_sound.play(maxtime=800)
except KeyboardInterrupt:
    ser.close()
