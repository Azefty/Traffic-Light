int redLed = 10;
int yellowLed = 9;
int greenLed = 8;


long t_red = 20000;    
long t_yellow = 20000;  
long t_green = 20000;   


int currentState = 0;  
long previousMillis = 0; 


bool isYellowToGreen = true;

void setup() {
  
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}

void loop() {
  
  unsigned long currentMillis = millis();

  switch (currentState) {
    case 0: 
      if (currentMillis - previousMillis >= t_red) {
        currentState = 1; 
        isYellowToGreen = true; 
        previousMillis = currentMillis; 
      }
      
      digitalWrite(redLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);
      break;

    case 1: 
      if (currentMillis - previousMillis >= t_yellow) {
        if (isYellowToGreen) {
          currentState = 2;
        } else {
          currentState = 0; 
        }
        previousMillis = currentMillis; 
      }
      
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, LOW);
      break;

    case 2: 
      if (currentMillis - previousMillis >= t_green) {
        currentState = 1; 
        isYellowToGreen = false;
        previousMillis = currentMillis;
      }
      
      digitalWrite(redLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, HIGH);
      break;
  }
}