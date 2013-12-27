
#ifndef SerialSevenSegment_h
#define SerialSevenSegment_h

#include "Arduino.h"

class SerialSevenSegment
{
  public:
    SerialSevenSegment(HardwareSerial &s);
	SerialSevenSegment();
    void clearDisplay();
	void clearDecimals();
	
    void setDecimals(byte decimals);
	void setBrightness(byte value);
	
	void toggleAposOn();
	void toggleAposOff();
	
	void toggleColonOn();
	void toggleColonOff();
	
	void toggleDecimalPointOn(int location);
	void toggleDecimalPointOff(int location);
	
	void writeNumbers(unsigned int numbers);
	void writeClock(unsigned int minutes, unsigned int seconds);
	
  private:
	char _datastring[10];
	bool colonState;
	byte _decimals;
	HardwareSerial* _ser;
};

#endif
