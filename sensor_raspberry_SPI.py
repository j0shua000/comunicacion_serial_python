import spidev
import time

class ArduinoTemperature:
    def __init__(self, bus, device, max_speed_hz):
        self.bus = bus
        self.device = device
        self.max_speed_hz = max_speed_hz
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.device)
        self.spi.max_speed_hz = self.max_speed_hz

    def read_temperature(self):
        high_byte = self.spi.xfer2([0x00])[0]
        low_byte = self.spi.xfer2([0x00])[0]
        temp_int16 = (high_byte << 8) | low_byte
        temperature = temp_int16 / 100.0
        return temperature

    def close(self):
        self.spi.close()

def main():
    bus = 0
    device = 0
    max_speed_hz = 500000

    arduino_temperature = ArduinoTemperature(bus, device, max_speed_hz)

    try:
        while True:
            temperature = arduino_temperature.read_temperature()
            print("Temperatura medida: {:.2f} °C".format(temperature))
            time.sleep(30)
    except KeyboardInterrupt:
        print("\nTerminando la lectura de temperatura...")
    finally:
        arduino_temperature.close()

if __name__ == "__main__":
    main()
