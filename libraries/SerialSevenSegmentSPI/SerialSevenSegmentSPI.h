
#ifndef SerialSevenSegmentSPI_h
#define SerialSevenSegmentSPI_h

#include "Arduino.h"

class SerialSevenSegment
{
  public:
    SerialSevenSegment(int slaveSelectPin, HardwareSerial &ser);
	SerialSevenSegment();
    void clearDisplay();
	void clearDecimals();
	void init();
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
	
	void write(const char buf[], uint8_t len);
	
	void display(const char digits[4]);
	void display(char dig1, char dig2, char dig3, char dig4);
	void spi_out_command(byte command, byte data);
	void spi_out_display(byte digit1, byte digit2, byte digit3, byte digit4);
	void CharToByte(char* chars, byte* bytes, unsigned int count);
	void ByteToChar(byte* bytes, char* chars, unsigned int count);
	
  private:
	char _datastring[10];
	bool colonState;
	int _slaveSelectPin;
	byte _decimals;
	HardwareSerial* _ser;
};

#endif

/*
#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#if ARDUINO >= 100
  #include <Arduino.h> // Arduino 1.0
#else
  #include <WProgram.h> // Arduino 0022
#endif

#include <SPI.h>
#include <stdint.h>


#define SEVENSEG_A  (1 << 0)
#define SEVENSEG_B  (1 << 1)
#define SEVENSEG_C  (1 << 2)
#define SEVENSEG_D  (1 << 3)
#define SEVENSEG_E  (1 << 4)
#define SEVENSEG_F  (1 << 5)
#define SEVENSEG_G  (1 << 6)


class SevenSeg {
private:
  uint8_t slaveSelectPin;

public:
  SevenSeg(uint8_t slaveSelectPin);

  void init();

  void write(const char buf[], uint8_t len);

  void display(char dig1, char dig2, char dig3, char dig4);
  void display(const char str[4]);
  void display(int16_t value);

  void setDigit(uint8_t position, uint8_t value);
  void setDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4);
  void setDecimalPoint(uint8_t value);

  void brightness(uint8_t value);
  void reset();
  void printError();
};

#endif

*/