int LEDPin[] = {3,4,5,6, 8,9,10,11};
int total = 0;
  
void setup(){
  
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);
  
  // Set up LED columns as output
  for(int pin = 0; pin < 7 ; pin++ ){
    pinMode(LEDPin[pin],OUTPUT);
    digitalWrite(LEDPin[pin],LOW);
  }

}


int incomingByte = 0;	// for incoming serial data
int x;

void loop(){
  // send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:

                
                x = incomingByte-48;
       
                if(x>=0 && x<=7) {
                  total = x;
                
                  
                  showFrame();
                  
		  //Serial.println(total);
                }
                
                incomingByte = 0;
                
                
	}


}

void showFrame() {
    
      for(int led = 0; led < 7; led++) {
          if(led<total) {
              digitalWrite(LEDPin[led],HIGH);
              Serial.print("ON  :");
              Serial.print(led);
              Serial.print("  ");
              Serial.println(LEDPin[led]);
          } else {
              digitalWrite(LEDPin[led],LOW);
              Serial.print("OFF :");
              Serial.print(led);
              Serial.print("  ");
              Serial.println(LEDPin[led]);
          }
      }
      
      Serial.println("           ");
      Serial.println("           ");
      Serial.println("           ");
  
}

