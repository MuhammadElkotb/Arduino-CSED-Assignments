#include <IRremote.h>



#define recPin 3
#define ledPin 12

IRrecv irrecv(recPin);
decode_results results;


unsigned long lastBlinkTime = 0;        // Last Time the LED Blinked in ms
int blinkRate = 0;  // Blink rate Controlled by user    
int high = 0;       // flag for HIGH or LOW LED OUTPUT


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(recPin, INPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
  }
  
  
  
void loop(){

  
 
 
   if(irrecv.decode(&results)){
    
    long remoteInVal = results.value;
    
    irrecv.resume();
    
    switch(remoteInVal){
      case 33444015 : blinkRate = 100;  break;            // Button (1)
      case 33478695 : blinkRate = 200;  break;            // Button (2)
      case 33486855 : blinkRate = 300;  break;            // Button (3)
      case 33435855 : blinkRate = 400;  break;            // Button (4)
      case 33468495 : blinkRate = 500;  break;            // Button (5)
      case 33452175 : blinkRate = 600;  break;            // Button (6)
      case 33423615 : blinkRate = 700;  break;            // Button (7)
      case 33484815 : blinkRate = 800;  break;            // Button (8)
      case 33462375 : blinkRate = 900;  break;            // Button (9)
      case 33480735 : blinkRate = 0;                      // Button (0)
      default : break;
      
    }
  }
  // if Button (0) then always high
  if(blinkRate == 0){
    high = 1;
  }

  // Blinking Rate Controller 
  while(millis() - lastBlinkTime > blinkRate){

    lastBlinkTime = millis();
    if(high){
      digitalWrite(ledPin, HIGH);
      high = 0;
    }
    else{
      digitalWrite(ledPin, LOW);
      high = 1;
    }
  }

  Serial.println(blinkRate);

  
  

  
     
  
} 
