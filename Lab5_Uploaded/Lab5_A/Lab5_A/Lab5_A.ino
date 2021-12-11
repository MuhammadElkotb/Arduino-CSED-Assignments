#include <IRremote.h>
#include <NewTone.h>
#include <LiquidCrystal.h>


#define recPin 6
#define buzzerPin 7
#define ledPin 13

IRrecv irrecv(recPin);
decode_results results;

unsigned long lastPrintTime = 0;
String threshold = "";
String sensorThreshold = "0";
int remoteInputLength  = 0;



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(recPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.

}



void loop() {
  float analogValue = analogRead(A0);
  float mv = (analogValue / 1023) * 5000;
  float celsius = mv / 10;



  if (irrecv.decode(&results)) {

    long remoteInVal = results.value;

    irrecv.resume();

    switch (remoteInVal) {
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


  

  if (celsius > sensorThreshold.toInt()) {
    lcd.clear();
    digitalWrite(ledPin, HIGH);
    NewTone(buzzerPin, 3000);
    lcd.setCursor(0, 0);
    lcd.print("Warning high temp");
    lcd.setCursor(0, 1);
    lcd.print(celsius);
    lcd.print("  ");
    lcd.print(sensorThreshold.toInt());
    lcd.print("  ");
    lcd.print(threshold);
    

    Serial.println(celsius);

  }
  else {
    lcd.clear();
    digitalWrite(ledPin, LOW);
    noNewTone(buzzerPin);
    Serial.println(celsius); 
    lcd.setCursor(0, 0);
    lcd.print("Max Temp: ");
    lcd.print(sensorThreshold.toInt());
    lcd.setCursor(0, 1);
    lcd.print(celsius);
    lcd.print("  ");
    lcd.print(threshold);
    

  }

    lastPrintTime = millis();

    Serial.print(threshold);
    Serial.print(" ");
    Serial.print(celsius);
    Serial.print(" ");
    Serial.print(sensorThreshold + "\n");




  }
