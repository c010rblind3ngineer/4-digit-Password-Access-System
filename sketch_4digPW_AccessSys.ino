/* Arduino 4-digit password access system.

   Components:
                - Arduino Uno
                - 4 x push button tactile switch
                - 4 x 1kOhm resistor
                - 3 x 220Ohm resistor
                - 10kOhm potentiometer
                - Passive buzzer
                - Red LED
                - Green LED
                - LCD
                - Some jumper wires

   Libraries:
                - LiquidCrystal library

   Documentations: https://en.wikipedia.org/wiki/Telephone_keypad

   Created on 19 June 2022 by arazak467
*/

const int btn1 = A1;
const int btn2 = A2;
const int btn3 = A3;
const int btn4 = A4;
const int redLED = A0;
const int buzzerPin = A5;
const int greenLED = 6;

int notes[] = {1209, 1336, 1477, 1633}; // frequencies referenced from wikipedia link above
int userInput [5] ;
int password [5] = {2, 3, 4, 1};
// TAKE NOTE: The number of 'beeps' correspond to the MISMATCHED user input and password,
// Example... User input = 1, 2, 4, 3.... 
// The number '4' here is at the same position as the password array number '4',
// so the beep will happen only 3 times during "Access Denied" since the rest of the 
// numbers in the array doesn't match each other.
int keyCounter = 0;

char entryOK [] = "Access Granted";
char entryNOTOK [] = "Access Denied";

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  lcd.print("Enter 4-digit");
  lcd.setCursor(0, 1);
  lcd.print("password: ");
  lcd.blink();

  // 'for' loop ensures the User only press 4 buttons
  for (int i = 0; i < 4;) { 

    if (digitalRead(btn1) == HIGH) {  // button 1 pressed
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, notes[0]);

      lcd.print("1");
      userInput[i] = 1;
      i++;
      delay(250);
    }
    else if (digitalRead(btn2) == HIGH) { // button 2 pressed
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, notes[1]);

      lcd.print("2");
      userInput[i] = 2;
      i++;
      delay(250);
    }
    else if (digitalRead(btn3) == HIGH) { // button 3 pressed
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, notes[2]);

      lcd.print("3");
      userInput[i] = 3;
      i++;
      delay(250);
    }
    else if (digitalRead(btn4) == HIGH) { // button 4 pressed
      digitalWrite(redLED, HIGH);
      tone(buzzerPin, notes[3]);

      lcd.print("4");
      userInput[i] = 4;
      i++;
      delay(250);
    }
    else {
      digitalWrite(redLED, LOW);
      digitalWrite(btn1, LOW);
      digitalWrite(btn2, LOW);
      digitalWrite(btn3, LOW);
      digitalWrite(btn4, LOW);
      noTone(buzzerPin);
    }
  }
  lcd.noBlink();
  lcd.clear();
  noTone(buzzerPin);
  digitalWrite(redLED, LOW);

  // 'for' loop check if the 4-digit password is the same as User input
  for (int j = 0; j < 4; j++) {
    if (userInput[j] == password[j]) {
      keyCounter++;
      //...Access Granted...
      if (keyCounter == 4) {
        digitalWrite(greenLED, HIGH);
        tone(buzzerPin, 2000);
        delay(100);
        noTone(buzzerPin);
        delay(100);
        tone(buzzerPin, 2000);
        delay(100);
        noTone(buzzerPin);
        lcd.noBlink();        
        lcd.print(entryOK);
        delay(2000);
        keyCounter = 0;
        lcd.clear();
      }
    }
    //...Access Denied...
    else {
      digitalWrite(redLED, HIGH);
      lcd.noBlink();
      lcd.print(entryNOTOK);
      delay(100);
      tone(buzzerPin, 500);
      delay(250);
      noTone(buzzerPin);
      keyCounter = 0;
      lcd.clear();
    }
  }
  // reset LCD
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  lcd.clear();
  delay(500);
}
