int pin = 5;
void setup() {
  pinMode(pin, OUTPUT);
  
 
}

void loop() {
  digitalWrite(pin, HIGH);  // Turn LED on
  delay(500);
  digitalWrite(pin, LOW);
}