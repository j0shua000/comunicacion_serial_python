import serial

ser = serial.Serial('/dev/ttyUSB0',9600)

while True:
	leerSerial = ser.readline()
	line = leerSerial.decode('utf-8').strip()
	print(line)