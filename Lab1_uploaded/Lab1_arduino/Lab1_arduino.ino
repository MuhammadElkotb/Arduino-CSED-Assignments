
String input;
bool morse[36][5] = {
      {0, 1}, //A
      {1, 0, 0, 0}, //B
      {1, 0, 1, 0}, //C
      {1, 0, 0}, //D
      {0}, //E
      {0, 0, 1, 0}, //F
      {1, 1, 0}, //G
      {0, 0, 0, 0}, //H
      {0, 0}, //I
      {0, 1, 1, 1}, //J
      {1, 0, 1}, //K
      {0, 1, 0, 0}, //L
      {1, 1}, //M
      {1, 0}, //N
      {1, 1, 1}, //O
      {0, 1, 1, 0}, //P
      {1, 1, 0, 1}, //Q
      {0, 1, 0}, //R
      {0, 0, 0}, //S 
      {1}, //T
      {0, 0, 1}, //U
      {0, 0, 0, 1}, //V
      {0, 1, 1}, //W
      {1, 0, 0, 1}, //X
      {1, 0, 1, 1}, //Y
      {1, 1, 0, 0}, //Z
      {1, 1, 1, 1, 1}, //0
      {0, 1, 1, 1, 1}, //1
      {0, 0, 1, 1, 1}, //2
      {0, 0, 0, 1, 1}, //3
      {0, 0, 0, 0, 1}, //4
      {0, 0, 0, 0, 0}, //5
      {1, 0, 0, 0, 0}, //6
      {1, 1, 0, 0, 0}, //7
      {1, 1, 1, 0, 0}, //8
      {1, 1, 1, 1, 0} //9
      };
      char morseLength[36] = {
        2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 4, 4, 3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
      };
    


void setup(){
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    
    
    
}


void representMorseCharacter(bool morseChar[], int n, int timeUnit){
  
    for(int i = 0; i < n; i++){
        if(morseChar[i] == 0){
            digitalWrite(13, HIGH);
            delay(timeUnit);
            digitalWrite(13, LOW);
            Serial.print(".");
        }
        if(morseChar[i] == 1){
            digitalWrite(13, HIGH);
            delay(timeUnit*3);
            digitalWrite(13, LOW);
            Serial.print("-");
        }
        delay(timeUnit);
    }
}






void loop(){
    int timeUnit = 300;
    
   
    
     if(Serial.available()){
      
     
      input = Serial.readStringUntil('\n');
      Serial.print(input + '\n');
      for(int i = 0; i < input.length(); i++){
        if(input[i]-'0' >= 0 && input[i]-'0' <= 9)
          representMorseCharacter(morse[input[i] - '0' + 26], morseLength[input[i] - '0' + 26], timeUnit);
        else if(input[i]>='A'&& input[i]<='Z')
          representMorseCharacter(morse[input[i] - 'A'], morseLength[input[i] - 'A'], timeUnit);
        else if(input[i]>='a'&& input[i]<='z')
          representMorseCharacter(morse[input[i] - 'a'], morseLength[input[i] - 'a'], timeUnit);
      }
      Serial.print('\n');
     }
    
    
    

   


}
