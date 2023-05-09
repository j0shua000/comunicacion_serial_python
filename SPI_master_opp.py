import spidev
import time

class SPICommunication:
    def _init_(self, bus, device, max_speed_hz):
        self.bus = bus
        self.device = device
        self.max_speed_hz = max_speed_hz
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.device)
        self.spi.max_speed_hz = self.max_speed_hz

    def read_data(self):
        message = ''
        self.spi.xfer2([0x00])  # Iniciar la transmisión desde el Arduino
        time.sleep(0.01)
        while True:
            data = self.spi.xfer2([0x00])
            character = chr(data[0])
            if character == '!':
                break
            message += character
            time.sleep(0.01)
        return message

    def close(self):
        self.spi.close()

if _name_ == "_main_":
    bus = 0
    device = 0
    max_speed_hz = 500000

    spi_communication = SPICommunication(bus, device, max_speed_hz)

    try:
        while True:
            message = spi_communication.read_data()
            print(f"Datos recibidos desde Arduino: {message}")
            time.sleep(1)

    except KeyboardInterrupt:
        print("Terminando comunicación SPI...")
        spi_communication.close()