
#ifndef Boksklok_h
#define Boksklok_h

#include "Arduino.h"
#include <Countdown.h>
#include <SerialSevenSegmentSPI.h>
#include <BoksklokConfig.h>

class Boksklok
{
  public:
    Boksklok(SerialSevenSegment &serialSevenSegment);
	void set(int programm);
	void wait(int seconds);
	void start();
	void setVisualInActive();
	void setVisualInRest();
  private:
    int _cycles; //a cycle is active and a rest moment.
	int _maxcycles;
	Countdown _active;
	Countdown _rest;
	SerialSevenSegment* _serialSevenSegment;
	BoksklokConfig bkCFG;
};

#endif