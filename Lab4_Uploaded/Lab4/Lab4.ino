#include <IRremote.h>
#include <NewTone.h>


IRrecv irrecv(recPin);
decode_results results;
#define recPin 3
#define buzzerPin 2
#define ledPin 13
#define DEBOUNCE_DELAY 700
#define PRINT_DELAY 500
unsigned long lastDebounceTime = 0;
unsigned long lastPrintTime = 0;
String threshold = "";
String sensorThreshold = "0";
int remoteInputLength  = 0;


void setup(){
	pinMode(ledPin, OUTPUT);
  pinMode(recPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
	}
	
	
	
void loop(){
	float analogValue = analogRead(A0);
  float mv = (analogValue / 1023) * 5000;
  float celsius = mv / 10;
  
  
  

  

  if(millis() - lastDebounceTime > DEBOUNCE_DELAY){
     if(irrecv.decode(&results)){
      
      long remoteInVal = results.value;
      lastDebounceTime = millis();
      irrecv.resume();
      
      switch(remoteInVal){
        case 33444015 : threshold.concat("1"); remoteInputLength ++; break; 
        case 33478695 : threshold.concat("2"); remoteInputLength ++; break;
        case 33486855 : threshold.concat("3"); remoteInputLength ++; break;
        case 33435855 : threshold.concat("4"); remoteInputLength ++; break;
        case 33468495 : threshold.concat("5"); remoteInputLength ++; break;
        case 33452175 : threshold.concat("6"); remoteInputLength ++; break;
        case 33423615 : threshold.concat("7"); remoteInputLength ++; break;
        case 33484815 : threshold.concat("8"); remoteInputLength ++; break;
        case 33462375 : threshold.concat("9"); remoteInputLength ++; break;
        case 33480735 : threshold.concat("0"); remoteInputLength ++; break;
        case 33431775 : threshold.remove(remoteInputLength - 1); remoteInputLength --; break;
        case 33441975 :  
                          sensorThreshold = threshold;
                          threshold = "";
                          break;
        default : break;
        
      }
    }
  }

  
  if(celsius > sensorThreshold.toInt()){
    digitalWrite(ledPin, HIGH);
    NewTone(buzzerPin, 3000);
    
    
  }
  else{
    digitalWrite(ledPin, LOW);
    noNewTone(buzzerPin);
    
  }

  if(millis() - lastPrintTime > PRINT_DELAY){
    Serial.println(threshold);
    Serial.print(sensorThreshold + " ");
    Serial.println(celsius);
    lastPrintTime = millis();
  }



  
    

  
}	
