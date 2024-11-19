class TrafficLight {
private:
  int redLed;
  int yellowLed;
  int greenLed;

  long t_red;
  long t_yellow;
  long t_green;

  int currentState;
  long previousMillis;
  bool isYellowToGreen;

public:
  
  TrafficLight(int redPin, int yellowPin, int greenPin, long redTime, long yellowTime, long greenTime) {
	redLed = redPin;
    yellowLed = yellowPin; 
    greenLed = greenPin;
    t_red = redTime;
    t_yellow = yellowTime; 
    t_green = greenTime;
    currentState = 0; 
    previousMillis = 0; 
    isYellowToGreen = true;   
  }

 
  void setup() {
    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(greenLed, OUTPUT);

    
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
  }

 
  void update() {
    unsigned long currentMillis = millis();

    switch (currentState) {
      case 0: 
        if (currentMillis - previousMillis >= t_red) {
          currentState = 1; 
          isYellowToGreen = true; 
          previousMillis = currentMillis;
        }
        setLights(HIGH, LOW, LOW);
        break;

      case 1: 
        if (currentMillis - previousMillis >= t_yellow) {
          currentState = isYellowToGreen ? 2 : 0; 
          previousMillis = currentMillis;
        }
        setLights(LOW, HIGH, LOW);
        break;

      case 2:
        if (currentMillis - previousMillis >= t_green) {
          currentState = 1;
          isYellowToGreen = false; 
          previousMillis = currentMillis;
        }
        setLights(LOW, LOW, HIGH);
        break;
    }
  }

private:
  
  void setLights(int redState, int yellowState, int greenState) {
    digitalWrite(redLed, redState);
    digitalWrite(yellowLed, yellowState);
    digitalWrite(greenLed, greenState);
  }
};


TrafficLight trafficLight(10, 9, 8, 2000, 2000, 2000);

void setup() {
  trafficLight.setup();
}

void loop() {
  trafficLight.update();
}
