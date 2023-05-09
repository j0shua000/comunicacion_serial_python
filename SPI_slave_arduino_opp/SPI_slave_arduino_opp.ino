#include <SPI.h>

class SpiSlave {
  public:
    void begin() {
      pinMode(SS, INPUT_PULLUP);
      SPI.begin();
      SPI.setBitOrder(MSBFIRST);
      SPI.setDataMode(SPI_MODE0);
    }
  
    void readData(byte* data, int len) {
      while (digitalRead(SS) == LOW);
      for (int i = 0; i < len; i++) {
        data[i] = SPI.transfer(0);
      }
    }
};

SpiSlave spiSlave;

void setup() {
  spiSlave.begin();
}

void loop() {
  // ...
}