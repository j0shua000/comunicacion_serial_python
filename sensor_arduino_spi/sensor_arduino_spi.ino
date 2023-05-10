#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>

const int TEMP_SENSOR_PIN = 2;
OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress deviceAddress;

const int SLAVE_SELECT_PIN = 10;
float temperature;

void setup() {
  Serial.begin(9600);  
  sensors.begin();
  sensors.getAddress(deviceAddress, 0);
  sensors.setResolution(deviceAddress, 12);

  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  digitalWrite(SLAVE_SELECT_PIN, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8); // Ajusta la velocidad del reloj si es necesario
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempC(deviceAddress);
  sendData(temperature);
  Serial.println(temperature);
  delay(30000);
}

void sendData(float temperature) {
  int16_t tempToSend = temperature * 100;
  byte highByte = highByte(tempToSend);
  byte lowByte = lowByte(tempToSend);

  byte dataToSend[] = {'S', highByte, lowByte, 'E'};

  digitalWrite(SLAVE_SELECT_PIN, LOW);
  delayMicroseconds(50);

  for (byte data : dataToSend) {
    SPI.transfer(data);
    delayMicroseconds(50);
  }

  digitalWrite(SLAVE_SELECT_PIN, HIGH);
}