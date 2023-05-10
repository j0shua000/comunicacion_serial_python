import spidev

# inicializar el dispositivo SPI
spi = spidev.SpiDev()
spi.open(0, 0)

# definir el pin de esclavo seleccionado
SLAVESELECT = 0

# leer los datos enviados desde Arduino
def read_data():
    resp = spi.xfer2([SLAVESELECT, 0])
    return resp[1]

# imprimir los datos en pantalla
while True:
    data = read_data()
    print("Datos recibidos desde Arduino: {}".format(data))