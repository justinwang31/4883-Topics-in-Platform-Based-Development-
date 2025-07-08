int redPin = 5;
int greenPin = 6;
int bluePin = 4;
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(1000);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  delay(1000);

  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  delay(1000);

  digitalWrite(bluePin, LOW);

}

void loop() {
 
   digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(10);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  delay(10);

  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  delay(10);

  digitalWrite(bluePin, LOW);
}