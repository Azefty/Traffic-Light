int redLed = 10;       
int yellowLed = 9;    
int greenLed = 8;     

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
  
  pinMode(pedRedLed, OUTPUT);
  pinMode(pedGreenLed, OUTPUT);
  pinMode(pedButton, INPUT_PULLUP);  

  
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  
  
  digitalWrite(pedRedLed, HIGH);
  digitalWrite(pedGreenLed, LOW);
}

void loop() {
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
      digitalWrite(redLed, HIGH);      
      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);

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

      digitalWrite(pedRedLed, LOW);    
      digitalWrite(pedGreenLed, HIGH);
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