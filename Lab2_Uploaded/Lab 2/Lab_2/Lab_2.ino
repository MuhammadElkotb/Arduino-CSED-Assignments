#define BUTTON_PIN 3          // macro for push button input pin --- > pin 3
#define RED_PIN 12            // macro for RED LED output pin ---> pin 12
#define GREEN_PIN 11          // macro for GREEN LED output pin ---> pin 11
#define DELAY 2000            // macro for 2000ms delay
#define DEBOUNCE_DELAY 300     //  macro for 300ms Debounce Delay for push button

int pushButton;               // int to indicate the state of the button (pressed/released) ---> (0/1)          
int ledRed;                   // int to indicate the state of the RED LED+
int ledGreen;                 // int to indicate the state of the GREEN LED
unsigned long int lastDebounceTime = 0;    // the time in ms when the push button was pressed                 
unsigned long int lastFlick = 0;           // the last time the LEDs changed states   
int red = 0;                               // int to organise the order of the RED and GREEN LEDs


void setup() {

  pinMode(BUTTON_PIN, INPUT_PULLUP);     // setup pin 13 for output
  pinMode(RED_PIN, OUTPUT);              // setup pin 12 for input
  pinMode(GREEN_PIN, OUTPUT);            // setup pin 11 for input
  Serial.begin(9600);
  
  
}



void loop() {
  pushButton = digitalRead(BUTTON_PIN);     // reads the state of the push button 
  ledRed = digitalRead(RED_PIN);            // reads the state of the RED LED 
  ledGreen = digitalRead(GREEN_PIN);        // reads the state of the GREEN LED

  
  
  if((millis() - lastDebounceTime) > DEBOUNCE_DELAY){
   
      if(pushButton == 0){
        
        lastDebounceTime = millis();
       
        lastFlick = millis();
     
        if(red == -1 && ledGreen){
          red = 1;
          digitalWrite(GREEN_PIN, LOW); 
          digitalWrite(RED_PIN, HIGH);
        
        
        }
        else if(red == -1 && ledRed){
          red = 0;
          digitalWrite(RED_PIN, LOW);
          digitalWrite(GREEN_PIN, HIGH);
       
        
        }
      }
      
      
     
    if(red == 1){
        digitalWrite(RED_PIN, HIGH);
        lastFlick = millis();
        red = -1;
    } 
    else if(red == 0){
        digitalWrite(GREEN_PIN, HIGH);
        lastFlick = millis();
        red = -1;
    }

    
    if((millis() - lastFlick > DELAY)){
 
        if(red == -1 && ledGreen){
          red = 1;
          digitalWrite(GREEN_PIN, LOW);
        }
      
        else if(red == -1 && ledRed){
          red = 0;
          digitalWrite(RED_PIN, LOW);
        }
    } 
  }  
}
