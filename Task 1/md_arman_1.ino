// Pin Definitions
int redLed = 10;
int yellowLed = 9;
int greenLed = 8;

// Timing for each state (in milliseconds)
long t_red = 20000;    // 10 seconds for Red
long t_yellow = 20000;  // 2 seconds for Yellow
long t_green = 20000;   // 8 seconds for Green

// Current state and time tracking
int currentState = 0;  // 0 = Red, 1 = Yellow, 2 = Green
long previousMillis = 0; 

// Variable to track Yellow's direction
bool isYellowToGreen = true;

void setup() {
  // Initialize LED pins as outputs
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Start with Red light ON
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}

void loop() {
  // Get the current time in milliseconds
  unsigned long currentMillis = millis();

  switch (currentState) {
    case 0: // Red Light State
      if (currentMillis - previousMillis >= t_red) {
        currentState = 1; // Move to Yellow
        isYellowToGreen = true; // Set Yellow to transition to Green
        previousMillis = currentMillis; // Reset timer
      }
      // Red LED ON, others OFF
      digitalWrite(redLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);
      break;

    case 1: // Yellow Light State
      if (currentMillis - previousMillis >= t_yellow) {
        if (isYellowToGreen) {
          currentState = 2; // Move to Green
        } else {
          currentState = 0; // Move back to Red
        }
        previousMillis = currentMillis; // Reset timer
      }
      // Yellow LED ON, others OFF
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);
      break;

    case 2: // Green Light State
      if (currentMillis - previousMillis >= t_green) {
        currentState = 1; // Move to Yellow
        isYellowToGreen = false; // Set Yellow to transition to Red
        previousMillis = currentMillis; // Reset timer
      }
      // Green LED ON, others OFF
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, HIGH);
      break;
  }
}