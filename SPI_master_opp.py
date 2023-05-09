import spidev
import time
import serial

class SPICommunication:
    def __init__(self, bus, device, max_speed_hz):
        self.bus = bus
        self.device = device
        self.max_speed_hz = max_speed_hz
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.device)
        self.spi.max_speed_hz = self.max_speed_hz

    def read_data(self, num_bytes):
        return self.spi.readbytes(num_bytes)

    def close(self):
        self.spi.close()

if __name__ == "__main__":
    bus = 0
    device = 0
    max_speed_hz = 500000

    spi_communication = SPICommunication(bus, device, max_speed_hz)

    try:
        while True:
            data = spi_communication.read_data(32)
            message = ''.join(chr(x) for x in data if x != 0)
            print(f"Datos recibidos desde Arduino: {message}")
            time.sleep(1)

    except KeyboardInterrupt:
        print("Terminando comunicación SPI...")
        spi_communication.close()