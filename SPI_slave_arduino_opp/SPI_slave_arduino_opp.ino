#include <SPI.h>

volatile byte receivedData;
volatile boolean dataReady;

void setup() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE) | _BV(SPIE);
  receivedData = 0;
  dataReady = false;
}

void loop() {
  if (dataReady) {
    SPDR = receivedData;
    dataReady = false;
  }
}

ISR(SPI_STC_vect) {
  byte data = SPDR;
  if (data == 1) {
    receivedData = 'H';
  } else if (data == 2) {
    receivedData = 'o';
  } else if (data == 3) {
    receivedData = 'l';
  } else if (data == 4) {
    receivedData = 'a';
  } else {
    receivedData = '!';
  }
  dataReady = true;
}