/***
=================
     WIRING
=================
KEYPAD

PIN KEYPAD  -  PIN ARDUINO
1           -  D7
2           -  D5
3           -  D8
4           -  D2
5           -  D6
6           -  D3
7           -  D4
RED         -  VCC (5 volt)
=================
SEVEN SEGMENT LED DISPLAY

VCC         - VCC (5 volt - Red wire)
GND         - GND (Brown wire)
RX			- D1  (TX - Serial)
=================
OTHERS 

Buzzer B	- D09
Buzzer A	- D10
Red Led		- D11
Green Led	- D12
Yellow Led	- D13
*/


/****************INCLUDE LIBRARIES****************/
//#include <SPI.h>
#include <stdint.h>
#include <BoksklokConfig.h>
#include <SerialSevenSegment.h>
#include <Countdown.h>
#include <Boksklok.h>
#include <Keypad.h>


/****************DEFINE VARIABLE****************/
//Visual and sound outputs for the machine-states
int pinRedLight=11; //Pin where the light is attached for inactive mode
int pinGreenLight=12; //Pin where the light is attached for active mode
int pinYellowLight=13; //Pin where the yellow light is attached for active mode
int pinBuzzerA=10; //Pin where the buzzer is attached
int pinBuzzerB=9; //Pin where the buzzer is attached
boolean bkloop=true;
boolean setrounds=false;

//Input vars using by the keypad
char numbers[2]; //Holds the two digits entered with the keypad
const byte ROWS = 4; //four rows of the keypad
const byte COLS = 3; //three columns of the keypad
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
}; //characters of the keypad, corresponding rows/cols,
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad


/****************INSTANTIATE OBJECTS****************/
SerialSevenSegment serialSevenSegment(Serial);
Boksklok bk(serialSevenSegment, pinGreenLight, pinRedLight, pinYellowLight, pinBuzzerA, pinBuzzerB);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned int programm=0;
unsigned int rounds=0;

void setup()
{
  numbers[0]='0';
  numbers[1]= '0';
  Serial.begin(9600);
  serialSevenSegment.writeNumbers(0);
  bk.toggleYellowLedOn();
}

void loop()
{
  delay(5);
  
  char key = keypad.getKey();

  if (key){
    if(key=='*'){
        bkloop=true;
        bk.set(programm);
        bk.wait(12);
        bk.toggleYellowLedOff();
        if(rounds==0){
            setrounds=false;
        }
        while(bkloop){
            bk.start(); //Never ending until reset. Maybe an escape will build in later.
            if(setrounds==true){
                rounds=rounds-1;
                if(rounds < 1){
                   bkloop=false;
                }
            }
        }
        
        /*AFTER FINISHING ROUNDS */
        numbers[0]='0';
        numbers[1]= '0';
        serialSevenSegment.writeNumbers(0);
        bk.toggleYellowLedOn();
        bk.setVisualInActive();
        bk.toggleGreenLedOff();
        bk.buzzer(4200);
        bk.toggleYellowLedOn();
        /***************************/
        
    }else if(key=='#'){
        numbers[0]='0';
        numbers[1]= '0';
        rounds = atoi(numbers); 
        serialSevenSegment.writeNumbers(rounds); 
        setrounds=true;
        
    }else{
        if(setrounds==false){
            numbers[0] = numbers[1];
            numbers[1] = key;
            programm = atoi(numbers); 
            serialSevenSegment.writeNumbers(programm);            
        }else{
            numbers[0] = numbers[1];
            numbers[1] = key;
            rounds = atoi(numbers); 
            serialSevenSegment.writeNumbers(rounds);           
        }
    }
  }
}

