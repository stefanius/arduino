#include "Arduino.h"
#include "SerialSevenSegment.h"

SerialSevenSegment::SerialSevenSegment(HardwareSerial &s)
{
	_ser = &s;
	clearDisplay();
	toggleColonOff();
	
}

SerialSevenSegment::SerialSevenSegment()
{

}

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void SerialSevenSegment::clearDisplay()
{
  _ser->write(0x76);  // Clear display command
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void SerialSevenSegment::setBrightness(byte value)
{
  _ser->write(0x7A);  // Set brightness command byte
  _ser->write(value);  // brightness data byte
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void SerialSevenSegment::setDecimals(byte decimals)
{
  _ser->write(0x77);
  _ser->write(decimals);
  _decimals=decimals;
}

void SerialSevenSegment::clearDecimals()
{
  setDecimals(0b00000000);
  colonState=false;
}

void SerialSevenSegment::toggleColonOn()
{
  setDecimals(0b00010000 | _decimals);
  colonState=true;
}

void SerialSevenSegment::toggleColonOff()
{
  setDecimals(0b11101111 & _decimals);
  colonState=false;
}

void SerialSevenSegment::toggleAposOn()
{
  setDecimals(0b00100000 | _decimals);
}

void SerialSevenSegment::toggleAposOff()
{
  setDecimals(0b11011111 & _decimals);
}

void SerialSevenSegment::toggleDecimalPointOn(int location)
{
  int l = location %4;
  if(l==1){
	setDecimals(0b00000001 | _decimals);
  }else if(l==2){
	setDecimals(0b00000010 | _decimals);
  }else if(l==3){
	setDecimals(0b00000100 | _decimals);
  }else if(l==0){
	setDecimals(0b00001000 | _decimals);
  }
  
}

void SerialSevenSegment::toggleDecimalPointOff(int location)
{
  int l = location %4;
  if(l==1){
	setDecimals(0b00000001 & _decimals);
  }else if(l==2){
	setDecimals(0b00000010 & _decimals);
  }else if(l==3){
	setDecimals(0b00000100 & _decimals);
  }else if(l==0){
	setDecimals(0b00001000 & _decimals);
  }
}

void SerialSevenSegment::writeNumbers(unsigned int numbers)
{
  sprintf(_datastring, "%4d", numbers);
  
  // This will output the tempString to the S7S
  _ser->print(_datastring);
}

void SerialSevenSegment::writeClock(unsigned int minutes, unsigned int seconds)
{
  sprintf(_datastring, "%2d%2d", minutes,seconds);  
  // This will output the tempString to the S7S
  _ser->print(_datastring);
  if(colonState==false){
	toggleColonOn();
  }else{
	toggleColonOff();
  }
}
