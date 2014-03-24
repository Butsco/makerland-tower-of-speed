//int LEDPin[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int LEDPin[] = {21,20,19,18,17,16,15,14,8,9,10,11,12,13,7,6};
int LayerPin[] = {A0, A1, A2, A3};
  
void setup(){
  
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);
  
  // Set up LED columns as output
  for(int pin = 0; pin < 16 ; pin++ ){
    pinMode(LEDPin[pin],OUTPUT);
    digitalWrite(LEDPin[pin],LOW);
  }
  // Set up LED Layers as output
  for(int layer = 0; layer < 4; layer++){
    pinMode(LayerPin[layer], OUTPUT);
    digitalWrite(LayerPin[layer], HIGH);
  }

}

boolean leds[4][16] = {
{
true,true,true,true,
true,true,true,true,
true,true,true,true,
true,true,true,true,
},{
false,false,false,false,
false,false,false,false,
false,false,false,false,
false,false,false,false
},{
false,false,false,false,
false,false,false,false,
false,false,false,false,
false,false,false,false
},{
false,false,false,false,
false,false,false,false,
false,false,false,false,
false,false,false,false
}
};


boolean draw = true;

// modes
int mode = 3;
int DROP = 1;
int DRUKKEUH =  2;
int NOTHING = 3;

// DROP mode
int frame = 0;
int dropFrames = 20;
int drop = random(0,16);
boolean down = true;

// DRUKKEUH
int frameD = 0;
int drukkeuh = 100; //random(100, 200);
// 250 == 4 sec
int dMin = 250;
int dMax = 1250;

// NOTHING
int nothing = 125;




int incomingByte = 0;	// for incoming serial data


void loop(){
  // send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:
		//Serial.println("I received: ");
		//Serial.println(incomingByte, DEC);

                if(incomingByte == 120) { toMode(DROP); }
                if(incomingByte == 122) { toMode(DRUKKEUH); }
                if(incomingByte == 99) { toMode(NOTHING); }
                
                incomingByte = 0;
	}
  
  
 
   
   showFrame();
   


  if(mode == DROP) {
    nextAnimationFrame();
    
    // timebomb
    drukkeuh--;
  
    if(drukkeuh==0) {
      //toMode(DRUKKEUH);
    }
  } else if(mode==DRUKKEUH) {
    nextDrukkeuhFrame();
  } else if(mode==NOTHING) {
    nothing--;
    
     if(nothing==0) {
      toMode(DROP);
    }
  }

}

void showFrame() {

 
    
   // display the leds data structure layer by layer
  for(int layer = 0; layer < 4; layer++) {

    
      for(int led = 0; led < 16; led++) {
          if(leds[layer][led]) {
              digitalWrite(LEDPin[led],HIGH);
          } else {
              digitalWrite(LEDPin[led],LOW);
          }
      }
   
      digitalWrite(LayerPin[layer],LOW);
      delay(4); 
      digitalWrite(LayerPin[layer],HIGH);
  }
  
}

void toMode(int m) {
  if(mode==m) {
    return;
  }
  
  if(m == DROP) {
    //Serial.println("DROP mode");
    frame = 0;
    drop = random(0,16);
    down = true;
    
    for(int led = 0; led < 16; led++) {
            leds[0][led] = true;
            leds[1][led] = false;
            leds[2][led] = false;
            leds[3][led] = false;
        }
    
    drukkeuh = random(dMin, dMax);
    drukkeuh = 250;
    //Serial.println(drukkeuh);
  } else if(m == DRUKKEUH) {
    //Serial.println("DRUKKEUH mode");
    frameD = 0;
    

  } else if(m == NOTHING) {
    nothing = 125;
     for(int layer = 0; layer < 4; layer++) {
          for(int led = 0; led < 16; led++) {
              leds[layer][led] = false;
          }
    
      }
  }
  
  mode = m;
}


boolean xx = false;

void nextDrukkeuhFrame() {
  
  frameD++;
  if(frameD%5==0) {
    xx = !xx;
    
    
    // display the leds data structure layer by layer
    for(int layer = 0; layer < 4; layer++) {
        for(int led = 0; led < 16; led++) {
            leds[layer][led] = xx;
        }
  
    }
    
  }
  
  if(frameD==200) {
    
    //toMode(NOTHING);
    
    frameD = 0;
  }
  
  

  
  
}


void nextAnimationFrame() {

  frame++;
  
  for(int layer = 0; layer < 4; layer++) {  
    
    if(down) {
      // every droplet of the ceiling will fall down
      
      leds[layer][drop] = ! ((frame/dropFrames - layer));
      
    } else {
      // the full floor rises to the top      
      
      for(int led = 0; led < 16; led++) {
         leds[layer][led] = ! ((frame/5 + layer+2)%5);
      }
      
    }
  }
  
  if (leds[down?3:0][drop])
  {
    // reset frame counter
    frame = 0;


    // when floor or ceiling is full, switch direction
    boolean reverse = true;

    for(int led = 0; led < 16; led++) {
        reverse = reverse && leds[down?3:0][led];
     }
     
     if(reverse) {
       down = !down;
     }
     
     // find the next droplet
     if(down) {
       do {
         drop = random(0,16);     
       } while(!leds[down?0:3][drop]);
     }
     
  } 
  
}


