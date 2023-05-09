import serial
import time

class ArduinoSerial:
    def __init__(self, port, baud_rate):
        self.port = port
        self.baud_rate = baud_rate
        self.serial_connection = None

    def connect(self):
        try:
            self.serial_connection = serial.Serial(self.port, self.baud_rate)
            print("Conexión establecida con éxito.")
            time.sleep(2)  # Damos tiempo para que la conexión se estabilice
        except Exception as e:
            print(f"Error al establecer conexión: {e}")

    def read_serial(self):
        if self.serial_connection:
            try:
                while True:
                    if self.serial_connection.in_waiting > 0:
                        data = self.serial_connection.readline().decode('utf-8').rstrip()
                        print(f"Datos recibidos desde Arduino: {data}")
            except KeyboardInterrupt:
                print("Cerrando conexión serial...")
                self.serial_connection.close()
        else:
            print("No hay conexión establecida. Utiliza el método 'connect()' para establecerla.")

if __name__ == "__main__":
    arduino_port = "/dev/ttyUSB0"  # Reemplaza con el puerto correspondiente en tu Raspberry Pi
    baud_rate = 9600

    arduino = ArduinoSerial(arduino_port, baud_rate)
    arduino.connect()
    arduino.read_serial()