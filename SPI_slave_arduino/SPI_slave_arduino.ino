#include <SPI.h>

// definir el pin de esclavo seleccionado
#define SLAVESELECT 10

void setup() {
  // Iniciar la comunicación SPI
  SPI.begin();
  // Configurar el pin de esclavo seleccionado como salida
  pinMode(SLAVESELECT, OUTPUT);
}

void loop() {
  // enviar los datos al dispositivo maestro
  digitalWrite(SLAVESELECT, LOW);
  SPI.transfer(42);
  digitalWrite(SLAVESELECT, HIGH);
  delay(1000);
}