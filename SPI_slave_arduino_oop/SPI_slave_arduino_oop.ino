#include <SPI.h>

const char dataToSend[] = "<Hola, desde Arduino!>";
volatile byte dataIndex = 0;

void setup() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE) | _BV(SPIE);
}

void loop() {
  delay(100);
}

ISR(SPI_STC_vect) {
  SPDR = dataToSend[dataIndex];
  dataIndex = (dataIndex + 1) % sizeof(dataToSend);
}
