class TrafficLightSystem {
  public:
    int greenLed;
    int yellowLed;
    int redLed;
    int p_greenLed;
    int p_redLed;
    int pushButton;

    long t_green;
    long t_yellow;
    long t_red;
    long t_pedestrianGreen;

    int currentState;
    long previousMillis;
    bool pedestrianRequest;

    // Constructor
    TrafficLightSystem() {
      greenLed = 8;
      yellowLed = 9;
      redLed = 10;
      p_greenLed = 2;
      p_redLed = 3;
      pushButton = 4;

      t_green = 20000;  // Time for green light
      t_yellow = 2000;  // Time for yellow light
      t_red = 20000;  // Time for red light

      currentState = 0;
      previousMillis = 0;
      pedestrianRequest = false;
    }

    void setup() {
      pinMode(greenLed, OUTPUT);
      pinMode(yellowLed, OUTPUT);
      pinMode(redLed, OUTPUT);
      pinMode(p_greenLed, OUTPUT);
      pinMode(p_redLed, OUTPUT);
      Serial.begin(9600);
      
      pinMode(pushButton, INPUT_PULLUP);

      digitalWrite(greenLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, LOW);

      
      Serial.write('g');
      Serial.write('R'); 

    }

    void update() {
      unsigned long currentMillis = millis();
      
      // Check if the pushbutton is pressed
      if (digitalRead(pushButton) == LOW) {
        pedestrianRequest = true;  
      }

      switch (currentState) {
        case 0:  
          if (pedestrianRequest || currentMillis - previousMillis >= t_green) {
            currentState = 1;  
            previousMillis = currentMillis;
          }
          digitalWrite(greenLed, HIGH);
          digitalWrite(yellowLed, LOW);
          digitalWrite(redLed, LOW);
        
        Serial.write('g');
        Serial.write('R');
        break;

        case 1:  //Yellow light for cars, pedestrian red
          if (currentMillis - previousMillis >= t_yellow) {
            currentState = 2;
            previousMillis = currentMillis;
            
          }
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
          digitalWrite(redLed, LOW);
          //digitalWrite(p_greenLed, LOW);
          //digitalWrite(p_redLed, HIGH);
        	Serial.write('g');
        	Serial.write('R');
          break;

        case 2:  // Red light for cars, pedestrian green
          if (currentMillis - previousMillis >= t_red) {
            currentState = 3;
            previousMillis = currentMillis;
            
          }
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, LOW);
          digitalWrite(redLed, HIGH);
          
		Serial.write('r');
        Serial.write('G');
        break;

        case 3:  // Pedestrian crossing
          if (currentMillis - previousMillis >= t_pedestrianGreen) {
            currentState = 4;  //Switch back to car green
            pedestrianRequest = false;  //Reset pedestrian request
            previousMillis = currentMillis;
          }
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, LOW);
          digitalWrite(redLed, HIGH);
          
          Serial.write('r');
          Serial.write('G');
          break;

        case 4:  // Transition back: car yellow, then car green
          if (currentMillis - previousMillis >= t_yellow) {
            currentState = 0;
            previousMillis = currentMillis;
          }
          digitalWrite(greenLed, LOW);
          digitalWrite(yellowLed, HIGH);
          digitalWrite(redLed, LOW);
          
        Serial.write('g');
        Serial.write('R');
          break;
      }
    }
};

// Instantiate the TrafficLightSystem object
TrafficLightSystem trafficLight;

void setup() {
  trafficLight.setup();
}

void loop() {
  trafficLight.update();
}