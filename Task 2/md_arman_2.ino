int redLed = 10;       // Traffic light red LED
int yellowLed = 9;    // Traffic light yellow LED
int greenLed = 8;     // Traffic light green LED

int pedRedLed = 3;     // Pedestrian red LED
int pedGreenLed = 2;   // Pedestrian green LED
int pedButton = 4;     // Pedestrian button

long t_red = 20000;     // Red light duration for cars
long t_yellow = 5000;  // Yellow light duration for cars
long t_green = 20000;  // Green light duration for cars
long t_pedGreen = 10000;  // Pedestrian green light duration after button press
long t_transitionDelay = 2000; // 2-second transition delay after button press

int currentState = 0;  // Traffic light state
long previousMillis = 0;
bool pedestrianRequest = false; // Tracks if the pedestrian button was pressed
bool isPedestrianCrossing = false; // Tracks if the pedestrian light is green

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  pinMode(pedRedLed, OUTPUT);
  pinMode(pedGreenLed, OUTPUT);
  pinMode(pedButton, INPUT_PULLUP);  // Use INPUT_PULLUP for the button

  // Initialize car lights: Red on, others off
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  
  // Initialize pedestrian lights: Red on, Green off
  digitalWrite(pedRedLed, HIGH);
  digitalWrite(pedGreenLed, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Check if pedestrian button is pressed
  if (digitalRead(pedButton) == LOW && !pedestrianRequest && !isPedestrianCrossing) {
    pedestrianRequest = true;  // Pedestrian requests to cross
  }

  if (pedestrianRequest) {
    // Handle pedestrian request: initiate transition delay
    currentState = 5;  // Move to the transition state (2-second delay)
    pedestrianRequest = false;  // Reset the pedestrian request
    previousMillis = currentMillis;
  }

  // Main state machine for traffic and pedestrian lights
  switch (currentState) {
    case 0: // Traffic light red, pedestrian light green
      if (currentMillis - previousMillis >= t_red) {
        currentState = 1;  // Change to yellow after red
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, HIGH);      // Traffic red
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(pedRedLed, LOW);    // Pedestrian green
      digitalWrite(pedGreenLed, HIGH);
      break;

    case 1: // Traffic light yellow, pedestrian light red
      if (currentMillis - previousMillis >= t_yellow) {
        currentState = 2;  // Change to green after yellow
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);       // Traffic yellow
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);

      digitalWrite(pedRedLed, HIGH);   // Pedestrian red
      digitalWrite(pedGreenLed, LOW);
      break;

    case 2: // Traffic light green, pedestrian light red
      if (currentMillis - previousMillis >= t_green) {
        currentState = 3;  // Change to yellow after green
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);       
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, HIGH);    // Traffic green

      digitalWrite(pedRedLed, HIGH);   // Pedestrian red
      digitalWrite(pedGreenLed, LOW);
      break;

    case 3: // Traffic light yellow, pedestrian light red
      if (currentMillis - previousMillis >= t_yellow) {
        currentState = 0;  // Change back to red after yellow
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);   // Traffic yellow
      digitalWrite(greenLed, LOW);

      digitalWrite(pedRedLed, HIGH);   // Pedestrian red
      digitalWrite(pedGreenLed, LOW);
      break;

    case 4: // Pedestrian crossing, traffic light red, pedestrian light green
      if (currentMillis - previousMillis >= t_pedGreen) {
        currentState = 0;  // After pedestrian green, return to normal state (traffic red)
        isPedestrianCrossing = false;  // Pedestrian crossing is done
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, HIGH);      // Traffic red
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(pedRedLed, LOW);    // Pedestrian green
      digitalWrite(pedGreenLed, HIGH);
      break;

    case 5: // Transition delay state (2-second delay)
      if (currentMillis - previousMillis >= t_transitionDelay) {
        currentState = 4;  // After 2 seconds, move to pedestrian green state
        isPedestrianCrossing = true;  // Pedestrian is crossing
        previousMillis = currentMillis;
      }
      // During the delay, traffic lights stay unchanged
      break;
  }
}
