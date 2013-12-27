//#include "Arduino.h"
#include <SPI.h>
//#include <stdint.h>
#include "SerialSevenSegmentSPI.h"


SerialSevenSegment::SerialSevenSegment(int slaveSelectPin, HardwareSerial &ser)
{
	this->_slaveSelectPin = slaveSelectPin;
    pinMode(_slaveSelectPin, OUTPUT);
	init();
	_ser =&ser;
	//toggleColonOff();
}

SerialSevenSegment::SerialSevenSegment()
{

}

void SerialSevenSegment::toggleAposOn()
{

}
void SerialSevenSegment::toggleAposOff()
{

}
	
void SerialSevenSegment::init(){
    SPI.setBitOrder(MSBFIRST);
    // The maximum speed of the display is 250kHz
    SPI.setClockDivider(SPI_CLOCK_DIV64);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();
	//clearDisplay();
}
// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void SerialSevenSegment::clearDisplay()
{
  digitalWrite(_slaveSelectPin, LOW); // enable device
    delay(30);
   SPI.transfer(0x76);
   digitalWrite(_slaveSelectPin, HIGH); // enable device
}


void SerialSevenSegment::writeNumbers(unsigned int numbers)
{
	char display[4];
	byte displaybyte[4];
	
	display[0]='0';
	display[3]='0';
	display[2]='0';
	display[1]='0';
	if(numbers < 10){
		display[0] = 0;
		display[1] = numbers;
	}else if(numbers < 100){
		char tmp_m [3];
		sprintf (tmp_m, "%2i", numbers);
		display[0] = tmp_m[0];
		display[1] = tmp_m[1];		
	}else if(numbers < 1000){
		char tmp_m [4];
		sprintf (tmp_m, "%3i", numbers);
		display[0] = tmp_m[0];
		display[1] = tmp_m[1];		
		display[2] = tmp_m[2];	
	}else if(numbers < 10000){
		char tmp_m [4];
		sprintf (tmp_m, "%4i", numbers);
		display[0] = tmp_m[0];
		display[1] = tmp_m[1];		
		display[2] = tmp_m[2];	
		display[3] = tmp_m[3];	
	}
	//spi_out_display('1','2','3','4');
	CharToByte(display, displaybyte, 4);
	
	spi_out_display(displaybyte[0], displaybyte[1], displaybyte[2],displaybyte[3]);
}

void SerialSevenSegment::writeClock(unsigned int minutes, unsigned int seconds)
{
	char display[4];
	byte displaybyte[4];
	
	display[0]='0';
	display[3]='0';
	display[2]='0';
	display[1]='0';
	
	if(minutes < 10){
		display[0] = 0;
		display[1] = minutes;
	}else{
		char tmp_m [3];
		sprintf (tmp_m, "%2i", minutes);
		display[0] = tmp_m[0];
		display[1] = tmp_m[1];		
	}

	if(seconds < 10){
		display[2] = 0;
		display[3] = seconds;
	}else{
		char tmp_s [3];
		sprintf (tmp_s, "%2i", seconds);
		display[2] = tmp_s[0];
		display[3] = tmp_s[1];		
	}
	
	spi_out_display(displaybyte[0], displaybyte[1], displaybyte[2],displaybyte[3]);
	//write(display,4);
}

void SerialSevenSegment::write(const char buf[], uint8_t len) 
{
    digitalWrite(this->_slaveSelectPin, LOW);
    delay(30);
	
    for(int i=0; i<len; i++) {
        SPI.transfer(buf[i]);
    }

    digitalWrite(this->_slaveSelectPin, HIGH);
}

void SerialSevenSegment::display(char dig1, char dig2, char dig3, char dig4) {
    char buf[4] = {dig1, dig2, dig3, dig4};
    write(buf, 4);
}

void SerialSevenSegment::display(const char digits[4]) {
    write(digits, 4);
}

void SerialSevenSegment::spi_out_command(byte command, byte data) {
  digitalWrite(_slaveSelectPin, LOW); // enable device
  delay(30);
   SPI.transfer(command);    // command
   if ( command != 0x76 ) {
     SPI.transfer(data);    // data
   }
  digitalWrite(_slaveSelectPin, HIGH); // disable device
}

void SerialSevenSegment::spi_out_display(byte digit1, byte digit2, byte digit3, byte digit4) {
  digitalWrite(_slaveSelectPin, LOW); // enable device
   delay(30);
   SPI.transfer(digit1);    // Thousands Digit
   SPI.transfer(digit2);    // Hundreds Digit
   SPI.transfer(digit3);    // Tens Digit
   SPI.transfer(digit4);    // Ones Digit
  digitalWrite(_slaveSelectPin, HIGH); // disable device
}

void SerialSevenSegment::CharToByte(char* chars, byte* bytes, unsigned int count){
    for(unsigned int i = 0; i < count; i++)
    	bytes[i] = (byte)chars[i];
}

void SerialSevenSegment::ByteToChar(byte* bytes, char* chars, unsigned int count){
    for(unsigned int i = 0; i < count; i++)
    	 chars[i] = (char)bytes[i];
}
/*
//
// SparkFun Seven Segment serial display library
// By Nicholas Humfrey
//
// With help from this forum post:
// http://arduino.cc/forum/index.php?topic=64362.0
//
// License: http://unlicense.org/
//

#include <SPI.h>
#include "SevenSeg.h"

SevenSeg::SevenSeg(uint8_t slaveSelectPin) {
    this->slaveSelectPin = slaveSelectPin;
}

void SevenSeg::init() {

    // Reset and blank the display
    reset();
}



void SevenSeg::reset() {

}

void SevenSeg::brightness(uint8_t value) {
    char buf[2] = {0x7A, value};
    write(buf, 2);
}



void SevenSeg::display(int16_t num) {
    const uint8_t base = 10;
    char digit[4] = { 0, ' ', ' ', ' ' };
    if (num > 9999) {
        // Number is too big
        printError();
    } else if (num < -999) {
        // Number is too small
        printError();
    } else if (num < 0) {
        uint16_t place = 0;
        num = (num ^ -1) + 1; // pretend num is positive
        while ( num && place < 4 ) {
            if ( num > 0 ) digit[place++] = num%base;
            num /= base;
        }
        digit[place] = '-'; // place negative sign appropriately
        display(digit[3], digit[2], digit[1], digit[0]);
    } else {
        uint16_t place = 0;
        while ( num && place < 4 ) {
            if ( num > 0 ) digit[place++] = num%base;
            num /= base;
        }
        display(digit[3], digit[2], digit[1], digit[0]);
    }
}

void SevenSeg::setDigit(uint8_t position, uint8_t value)
{
    char buf[2] = {0x7A+position, value};
    write(buf, 2);
}

void SevenSeg::setDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4)
{
    char buf[8] = {0x7B, dig1, 0x7C, dig2, 0x7D, dig3, 0x7E, dig4};
    write(buf, 8);
}

void SevenSeg::setDecimalPoint(uint8_t value)
{
    char buf[2] = {0x77, value};
    write(buf, 2);
}

void SevenSeg::printError(void) {
    write("oUER", 4);
}

*/