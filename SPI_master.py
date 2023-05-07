# Importamos los paquetes necesarios
import RPi.GPIO as GPIO #Para controlar pines de la tarj$
import spidev #Para implementar comunicación SPI
import time

GPIO.setmode(GPIO.BCM) #Definimos el modo para referirnos a los pines de la Raspberry Pi

spi = spidev.SpiDev() #Creamos el objeto spi
spi.open(0,0) #Abrimos el puerto SPI - Módulo 0, Dispositivo 0
spi.max_speed_hz = 5000 #Establecemos la velocidad máxima -->muy importante<--
try:
    while True:
        comando = input("Ingresar comando (on/off): ") #Solicitamos ingresar comando
        comando = comando + "\n" #Agregamos salto de línea al final del comando ingresado
        comando = comando.encode() #Convertimos el comando a un arreglo de bytes
        spi.xfer(comando) #Mandamos el comando
        time.sleep(0.25) #Esperamos 0.25

except KeyboardInterrupt:
    # Ctrl+C
    print ("Interrupción por teclado")
finally:
    spi.close()
    GPIO.cleanup()
    print ("GPIO.cleanup() y spi.close() ejecutados ")