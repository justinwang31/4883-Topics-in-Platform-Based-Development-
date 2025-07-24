const int trigPin = 9;
const int echoPin = 10;
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

const int thresholds[] = {10, 15, 20, 25, 30, 35};

void setup() {
  Serial.begin(9600);
 
  // Sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  // LED setup
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}


void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read echo with timeout (100ms)
  long duration = pulseIn(echoPin, HIGH, 100000);
  float distance = duration * 0.034 / 2;
 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
 
  // Reset all LEDs to OFF first
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
 
  // Light up LEDs based on distance (bar effect)
  if (distance <= 35) {  // Only activate if within range
    for (int i = 0; i < numLeds; i++) {
      if (distance <= thresholds[i]) {
        digitalWrite(ledPins[i], HIGH);
      }
    }
  }


 
  delay(100); // Small delay to stabilize readings
}
