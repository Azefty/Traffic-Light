int redLed = 13;
int yellowLed = 12;
int greenLed = 11;

int d2RedLed = 7;
int d2YellowLed = 6;
int d2GreenLed = 5;

int d3RedLed = 10;
int d3YellowLed = 9;
int d3GreenLed = 8;

int pedRedLed = 3;
int pedGreenLed = 2;
int pedButton = 4;

long t_red = 20000;
long t_yellow = 5000;
long t_green = 20000;
long t_pedGreen = 10000;
long t_transitionDelay = 2000;

int currentState = 0;
long previousMillis = 0;
bool pedestrianRequest = false;
bool isPedestrianCrossing = false;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  pinMode(d2RedLed, OUTPUT);
  pinMode(d2YellowLed, OUTPUT);
  pinMode(d2GreenLed, OUTPUT);

  pinMode(d3RedLed, OUTPUT);
  pinMode(d3YellowLed, OUTPUT);
  pinMode(d3GreenLed, OUTPUT);

  pinMode(pedRedLed, OUTPUT);
  pinMode(pedGreenLed, OUTPUT);
  pinMode(pedButton, INPUT_PULLUP);

  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);

  digitalWrite(d2RedLed, HIGH);
  digitalWrite(d2YellowLed, LOW);
  digitalWrite(d2GreenLed, LOW);

  digitalWrite(d3RedLed, LOW);
  digitalWrite(d3YellowLed, LOW);
  digitalWrite(d3GreenLed, HIGH);

  digitalWrite(pedRedLed, HIGH);
  digitalWrite(pedGreenLed, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (digitalRead(pedButton) == LOW && !pedestrianRequest && !isPedestrianCrossing) {
    pedestrianRequest = true;
  }

  if (pedestrianRequest) {
    currentState = 6;
    pedestrianRequest = false;
    previousMillis = currentMillis;
  }

  switch (currentState) {
    case 0:
      if (currentMillis - previousMillis >= t_red) {
        currentState = 1;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(d2RedLed, HIGH);
      digitalWrite(d2YellowLed, LOW);
      digitalWrite(d2GreenLed, LOW);

      digitalWrite(d3RedLed, LOW);
      digitalWrite(d3YellowLed, LOW);
      digitalWrite(d3GreenLed, HIGH);

      digitalWrite(pedRedLed, LOW);
      digitalWrite(pedGreenLed, HIGH);
      break;

    case 1:
      if (currentMillis - previousMillis >= t_yellow) {
        currentState = 2;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);

      digitalWrite(d2RedLed, LOW);
      digitalWrite(d2YellowLed, HIGH);
      digitalWrite(d2GreenLed, LOW);

      digitalWrite(d3RedLed, LOW);
      digitalWrite(d3YellowLed, HIGH);
      digitalWrite(d3GreenLed, LOW);

      digitalWrite(pedRedLed, HIGH);
      digitalWrite(pedGreenLed, LOW);
      break;

    case 2:
      if (currentMillis - previousMillis >= t_green) {
        currentState = 3;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, HIGH);

      digitalWrite(d2RedLed, LOW);
      digitalWrite(d2YellowLed, LOW);
      digitalWrite(d2GreenLed, HIGH);

      digitalWrite(d3RedLed, HIGH);
      digitalWrite(d3YellowLed, LOW);
      digitalWrite(d3GreenLed, LOW);

      digitalWrite(pedRedLed, HIGH);
      digitalWrite(pedGreenLed, LOW);
      break;

    case 3:
      if (currentMillis - previousMillis >= t_yellow) {
        currentState = 0;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);

      digitalWrite(d2RedLed, LOW);
      digitalWrite(d2YellowLed, HIGH);
      digitalWrite(d2GreenLed, LOW);

      digitalWrite(d3RedLed, LOW);
      digitalWrite(d3YellowLed, HIGH);
      digitalWrite(d3GreenLed, LOW);

      digitalWrite(pedRedLed, HIGH);
      digitalWrite(pedGreenLed, LOW);
      break;

    case 4:
      if (currentMillis - previousMillis >= t_pedGreen) {
        currentState = 0;
        isPedestrianCrossing = false;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(d2RedLed, HIGH);
      digitalWrite(d2YellowLed, LOW);
      digitalWrite(d2GreenLed, LOW);

      digitalWrite(d3RedLed, LOW);
      digitalWrite(d3YellowLed, LOW);
      digitalWrite(d3GreenLed, HIGH);

      digitalWrite(pedRedLed, LOW);
      digitalWrite(pedGreenLed, HIGH);
      break;

    case 5:
      if (currentMillis - previousMillis >= t_transitionDelay) {
        currentState = 4;
        isPedestrianCrossing = true;
        previousMillis = currentMillis;
      }
      digitalWrite(redLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

      digitalWrite(d2RedLed, HIGH);
      digitalWrite(d2YellowLed, LOW);
      digitalWrite(d2GreenLed, LOW);

      digitalWrite(d3RedLed, HIGH);
      digitalWrite(d3YellowLed, LOW);
      digitalWrite(d3GreenLed, LOW);

      digitalWrite(pedRedLed, HIGH);
      digitalWrite(pedGreenLed, LOW);
      break;

    case 6:
      // Immediate switch to yellow and delay before going red
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(d2GreenLed, LOW);
      digitalWrite(d2YellowLed, HIGH);

      digitalWrite(d3GreenLed, LOW);
      digitalWrite(d3YellowLed, HIGH);

      if (currentMillis - previousMillis >= t_transitionDelay) {
        digitalWrite(yellowLed, LOW);
        digitalWrite(redLed, HIGH);
        digitalWrite(d2YellowLed, LOW);
        digitalWrite(d2RedLed, HIGH);

        digitalWrite(d3YellowLed, LOW);
        digitalWrite(d3RedLed, HIGH);

        currentState = 4;
        previousMillis = currentMillis;
      }
      break;
  }
}
