/* @file EventSerialKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates using the KeypadEvent.
|| #
*/
#include <Keypad.h>
/*


PINNUMBERS ARE THE NUMBERS ON DE KEYPAD

Value  -  PINS
1:     -  2+3
2:     -  1+2
3:     -  2+5
4:     -  3+7
5:     -  1+7
6:     -  5+7
7:     -  3+6
8:     -  1+6
9:     -  5+6
*:     -  3+4
0:     -  1+4
#:     -  4+5

*/
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
	};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3,2,1}; //connect to the column pinouts of the keypad
	
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13; 
/*
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {8, 7, 6};
*/
boolean blink = false;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
  }
  if (blink){
    digitalWrite(ledPin,!digitalRead(ledPin));
    delay(100);
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){
        case '#': digitalWrite(ledPin,!digitalRead(ledPin)); break;
        case '*': 
          digitalWrite(ledPin,!digitalRead(ledPin));
        break;
      }
    break;
    case RELEASED:
      switch (key){
        case '*': 
          digitalWrite(ledPin,!digitalRead(ledPin));
          blink = false;
        break;
      }
    break;
    case HOLD:
      switch (key){
        case '*': blink = true; break;
      }
    break;
  }
}
