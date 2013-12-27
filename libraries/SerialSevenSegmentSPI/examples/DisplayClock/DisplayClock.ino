
#include <SerialSevenSegment.h>

unsigned int counter = 0;  // This variable will count up to 65k
SerialSevenSegment serialSevenSegment(Serial);


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

 // serialSevenSegment.clearDisplay();
  // This will output the tempString to the S7S

  //serialSevenSegment.setDecimals(0b00011111);  // Sets digit 3 decimal on
  
  counter++;  // Increment the counter
  serialSevenSegment.writeClock(2,counter);
  delay(1200);  // This will make the display update at 10Hz.

  
}

