int pin = 5;
void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  int potValue = analogRead(A3); // Read potentiometer
  int blinkDelay = map(potValue, 0, 1023, 100, 1000); // Map to 100ms–1s

  digitalWrite(pin, HIGH);  // Turn LED on
  delay(blinkDelay);
  digitalWrite(pin, LOW);
  delay(blinkDelay);
}