
#include <SerialSevenSegment.h>



unsigned int counter = 0;  // This variable will count up to 65k
SerialSevenSegment serialSevenSegment;


void setup()
{
  // Must begin s7s software serial at the correct baud rate.
  //  The default of the s7s is 9600.
  Serial.begin(9600);
  
  // Clear the display, and then turn on all segments and decimals
  serialSevenSegment.clearDisplay();  // Clears display, resets cursor
  serialSevenSegment.clearDecimals();  
}

void loop()
{

  serialSevenSegment.clearDisplay();
  // This will output the tempString to the S7S

  //serialSevenSegment.setDecimals(0b00011111);  // Sets digit 3 decimal on
  
  counter++;  // Increment the counter
  //delay(1200);  // This will make the display update at 10Hz.
  serialSevenSegment.toggleColonOn();  // Sets digit 3 decimal on
  delay(1200);  // This will make the display update at 10Hz.
  serialSevenSegment.toggleAposOn();  // Sets digit 3 decimal on
  delay(1200);  // This will make the display update at 10Hz.
  serialSevenSegment.toggleColonOff();  // Sets digit 3 decimal on
  delay(1200); 
  serialSevenSegment.toggleColonOn();  // Sets digit 3 decimal on
  delay(1200);  // This will make the display update at 10Hz.
  serialSevenSegment.toggleAposOff();  // Sets digit 3 decimal on
  delay(1200);  // This will make the display update at 10Hz.
  serialSevenSegment.toggleColonOff();  // Sets digit 3 decimal on
  delay(1200);  
  
  serialSevenSegment.toggleDecimalPointOn(1);
  delay(600);
  serialSevenSegment.toggleDecimalPointOn(2);
  delay(600);
  serialSevenSegment.toggleDecimalPointOn(3);
  delay(600);
  serialSevenSegment.toggleDecimalPointOn(4);
  delay(600);
  serialSevenSegment.toggleDecimalPointOff(5);
  delay(1000);
  serialSevenSegment.toggleDecimalPointOff(8);
  delay(1000);
  serialSevenSegment.clearDecimals();
  
}

