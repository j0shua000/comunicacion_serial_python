double numRandom;

void setup() {
  Serial.begin(9600);
}

void loop() {
  numRandom = random(0,100);

  Serial.println(numRandom);
  delay(500);

}