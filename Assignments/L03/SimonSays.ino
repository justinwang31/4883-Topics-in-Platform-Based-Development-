const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
int velocity = 1000;

const int inputPins[] = {A0, A1, A2, A3}; // Button inputs
const int ledPins[] = {2, 3, 4, 5};       // LED outputs
const int startButtonPin = A4;           // Start/Restart button

bool gameStarted = false;                // Game state tracker

void setup() {
  Serial.begin(9600); //  Enable Serial Monitor

  // Initialize input pins
  for (int i = 0; i < 4; i++) {
    pinMode(inputPins[i], INPUT);
  }

  pinMode(startButtonPin, INPUT_PULLUP);

  // Initialize output pins
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Seed randomness from unconnected analog pin
  randomSeed(analogRead(A6));
}

void loop() {
  // Start or restart game when button A4 is pressed
  if (!gameStarted && debounceButton(startButtonPin)) {
    reset_game_with_feedback();
    return;
  }

  // Game loop only runs if the game has started
  if (gameStarted) {
    Serial.print("🔁 Round ");
    Serial.println(level); // ✅ Print current round
    show_sequence();
    get_sequence();
  }
}

void show_sequence() {
  for (int i = 0; i < 4; i++)
    digitalWrite(ledPins[i], LOW);

  for (int i = 0; i < level; i++) {
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence() {
  int flag = 0;

  for (int i = 0; i < level; i++) {
    flag = 0;

    while (flag == 0) {
      if (debounceButton(startButtonPin)) {
        Serial.println("🔁 Game manually restarted.");
        reset_game_with_feedback();
        return;
      }

      for (int j = 0; j < 4; j++) {
        if (debounceButton(inputPins[j])) {
          digitalWrite(ledPins[3 - j], HIGH);  // Reverse to match button-LED pair
          your_sequence[i] = ledPins[3 - j];
          delay(200);

          if (your_sequence[i] != sequence[i]) {
            wrong_sequence();
            return;
          }

          digitalWrite(ledPins[3 - j], LOW);
          flag = 1;
        }
      }
    }
  }

  right_sequence();
}

void generate_sequence() {
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = ledPins[random(0, 4)]; // Choose LED pin (2–5)
  }
}

void wrong_sequence() {
  Serial.print("❌ Wrong sequence. You made it to round ");
  Serial.println(level); // ✅ Print the last round reached

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
    delay(250);
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
    delay(250);
  }

  level = 1;
  velocity = 1000;
  gameStarted = false;
}

void right_sequence() {
  for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
  delay(250);
  for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
  delay(500);
  for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
  delay(500);

  if (level < MAX_LEVEL)
    level++;

  if (velocity > 200)
    velocity -= 50;
}

bool debounceButton(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(20); // Simple debounce
    if (digitalRead(pin) == LOW) {
      while (digitalRead(pin) == LOW);
      return true;
    }
  }
  return false;
}

void reset_game_with_feedback() {
  Serial.println("🚀 Game started or restarted.");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
    delay(200);
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
    delay(200);
  }

  level = 1;
  velocity = 1000;
  generate_sequence();
  gameStarted = true;
}
