import spidev

class SpiMaster:
    def __init__(self, bus, device):
        self.spi = spidev.SpiDev()
        self.spi.open(bus, device)
        self.spi.max_speed_hz = 500000
    
    def transfer(self, data):
        return self.spi.xfer2(data)
    
spi = SpiMaster(0, 0) # Selecciona el bus SPI 0 y el dispositivo 0
data = [0x01, 0x02, 0x03]
response = spi.transfer(data)
print(response)    