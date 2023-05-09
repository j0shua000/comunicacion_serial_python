#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>

const int TEMP_SENSOR_PIN = 2;
OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);


DeviceAddress deviceAddress;

const int SLAVE_SELECT_PIN = 10;
volatile bool newDataAvailable = false;
volatile float temperature = 0;

void setup() {
  sensors.begin();
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, 12);

  pinMode(SLAVE_SELECT_PIN, INPUT);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
  SPI.begin();
  SPCR |= _BV(SPE) | _BV(SPIE);
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempC(deviceAddress);
  newDataAvailable = true;
  delay(30000);
}

ISR(SPI_STC_vect) {
  if (newDataAvailable) {
    int16_t tempToSend = temperature * 100;
    byte highByte = highByte(tempToSend);
    byte lowByte = lowByte(tempToSend);
    SPDR = highByte;
    delayMicroseconds(50);
    SPDR = lowByte;
    newDataAvailable = false;
  }
}