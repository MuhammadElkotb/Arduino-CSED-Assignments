#define analogPin A0            // macro for analog input A0
#define MAX_THRESHOLD 3         // macro for maximum voltage threshold
#define MIN_THRESHOLD 2.5       // macro for minimum voltage threshold
#define pinOUT 2                // macro for buzzer digital output
#define ledOUT 13               // macro for bulit-in  digital output LED
int analogVoltage = 0;          // analog pin input value
float outVoltage = 0;           // analog pin output value after mapping to voltage

void setup() {
  pinMode(pinOUT, INPUT);
  pinMode(ledOUT, OUTPUT);
  Serial.begin(9600);
}

/*
 * function to map analog input into voltages
 * returns a float of the mapped value
*/
float mapfloat(long x, long in_min, long in_max, long out_min, long out_max){
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void loop() {
  

  analogVoltage = analogRead(analogPin);
  outVoltage = mapfloat(analogVoltage, 0, 1023, 0, 5);    // value of the analog pin input in voltages

  Serial.print(outVoltage);

  /*
   * if-else code to check if the mapped voltage of the anaolog pin input 
  */
  if(outVoltage > MAX_THRESHOLD){
     digitalWrite(ledOUT, HIGH);
     tone(pinOUT, 3000);
  }
  
  else if(outVoltage < MIN_THRESHOLD){
    digitalWrite(ledOUT, LOW);
    noTone(pinOUT);
  }

  Serial.print("\n");

}
