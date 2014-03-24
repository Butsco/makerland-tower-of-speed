// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;
const int button1 = 2;
const int button2 = 3;

// LED read vars
String inputString = "";
boolean toggleComplete = false;
int buttonState1 = 0;
int buttonState2 = 0;

long lastDebounceTime = 0;
long debounceDelay = 400;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  digitalWrite(led,0);
}

// the loop routine runs over and over again forever:
void loop() {
  while (Serial.available() && toggleComplete == false){
    char inChar = (char)Serial.read();
    if(inChar == 'E'){
      toggleComplete = true;
    } else {
      inputString += inChar; 
    }
  }
  
  if(!Serial.available() && toggleComplete == true){
    int recievedVal = stringToInt();
    if(recievedVal == 0){
      digitalWrite(led,recievedVal);
    } else if (recievedVal == 1){
      digitalWrite(led,recievedVal);
    }
    toggleComplete = false;
  }

  if((millis() - lastDebounceTime)>debounceDelay){
    buttonState1 = digitalRead(button1);
    if (buttonState1 == HIGH){
      Serial.write("1");
      lastDebounceTime = millis();
    }
  }
  
  if((millis() - lastDebounceTime)>debounceDelay){
    buttonState2 = digitalRead(button2);
    if (buttonState2 == LOW){
      Serial.write("2");
      lastDebounceTime = millis();
    }
  }
    
  delay(50);
}

int stringToInt(){
  char charHolder[inputString.length()+1];
  inputString.toCharArray(charHolder,inputString.length()+1);
  inputString = "";
  int _recievedVal = atoi(charHolder);
  return _recievedVal;
}
