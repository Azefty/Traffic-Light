class TrafficLightSystem {
private:
    int redLed, yellowLed, greenLed;  
    int pedRedLed, pedGreenLed;       
    int pedButton;                    

    long t_red, t_yellow, t_green, t_pedGreen, t_transitionDelay;
    int currentState;
    long previousMillis;
    bool pedestrianRequest;
    bool isPedestrianCrossing;

public:
    TrafficLightSystem(int r, int y, int g, int pr, int pg, int pb) 
    {
      redLed = r; 
      yellowLed = y; 
      greenLed = g; 
      pedRedLed = pr;
      pedGreenLed = pg; 
      pedButton = pb; 
      t_red = 20000;
      t_yellow = 5000; 
      t_green = 20000; 
      t_transitionDelay = 2000;
      currentState = 0; 
      previousMillis = 0; 
      pedestrianRequest = false; 
      isPedestrianCrossing = false;
    }

    void setup() {
        pinMode(redLed, OUTPUT);
        pinMode(yellowLed, OUTPUT);
        pinMode(greenLed, OUTPUT);

        pinMode(pedRedLed, OUTPUT);
        pinMode(pedGreenLed, OUTPUT);
        pinMode(pedButton, INPUT_PULLUP);

        digitalWrite(redLed, HIGH);
        digitalWrite(yellowLed, LOW);
        digitalWrite(greenLed, LOW);

        digitalWrite(pedRedLed, HIGH);
        digitalWrite(pedGreenLed, LOW);
    }

    void update() {
        unsigned long currentMillis = millis();

        if (digitalRead(pedButton) == LOW && !pedestrianRequest && !isPedestrianCrossing) {
            pedestrianRequest = true;
        }

        if (pedestrianRequest) {
            currentState = 5;  
            pedestrianRequest = false;
            previousMillis = currentMillis;
        }

        switch (currentState) {
            case 0:
                if (currentMillis - previousMillis >= t_red) {
                    currentState = 1;
                    previousMillis = currentMillis;
                }
                setTrafficLightState(true, false, false, false, true);
                break;

            case 1:
                if (currentMillis - previousMillis >= t_yellow) {
                    currentState = 2;
                    previousMillis = currentMillis;
                }
                setTrafficLightState(false, true, false, true, false);
                break;

            case 2:
                if (currentMillis - previousMillis >= t_green) {
                    currentState = 3;
                    previousMillis = currentMillis;
                }
                setTrafficLightState(false, false, true, true, false);
                break;

            case 3:
                if (currentMillis - previousMillis >= t_yellow) {
                    currentState = 0;
                    previousMillis = currentMillis;
                }
                setTrafficLightState(false, true, false, true, false);
                break;

            case 4:
                if (currentMillis - previousMillis >= t_pedGreen) {
                    currentState = 0;
                    isPedestrianCrossing = false;
                    previousMillis = currentMillis;
                }
                setTrafficLightState(true, false, false, false, true);
                break;

            case 5:
                if (currentMillis - previousMillis >= t_transitionDelay) {
                    currentState = 4;
                    isPedestrianCrossing = true;
                    previousMillis = currentMillis;
                }
                break;
        }
    }

private:
    void setTrafficLightState(bool r, bool y, bool g, bool pr, bool pg) {
        digitalWrite(redLed, r ? HIGH : LOW);
        digitalWrite(yellowLed, y ? HIGH : LOW);
        digitalWrite(greenLed, g ? HIGH : LOW);
        digitalWrite(pedRedLed, pr ? HIGH : LOW);
        digitalWrite(pedGreenLed, pg ? HIGH : LOW);
    }
};

TrafficLightSystem trafficLight(10, 9, 8, 3, 2, 4);

void setup() {
    trafficLight.setup();
}

void loop() {
    trafficLight.update();
}
