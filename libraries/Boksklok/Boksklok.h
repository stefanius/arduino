
#ifndef Boksklok_h
#define Boksklok_h

#include "Arduino.h"
#include <Countdown.h>
#include <SerialSevenSegment.h>
#include <BoksklokConfig.h>

class Boksklok
{
  public:
    Boksklok(SerialSevenSegment serialSevenSegment, int pinGreenLight, int pinRedLight, int pinYellowLight,int pinBuzzerA, int pinBuzzerB);
	void set(int programm);
	void wait(int seconds);
	void start();
	void setVisualInActive();
	void setVisualInRest();
	void buzzer(int buzztime);
	void toggleYellowLedOn();
	void toggleYellowLedOff();
	void toggleGreenLedOn();
	void toggleGreenLedOff();
  private:
    int _cycles; //a cycle is active and a rest moment.
	int _maxcycles;
	Countdown _active;
	Countdown _rest;
	int _pinGreenLight; //Pin where the light is attached for active mode
	int _pinRedLight; //Pin where the light is attached for inactive mode
	int _pinYellowLight;
	int _pinBuzzerA; //Pin where the buzzer is attached
	int _pinBuzzerB;
	SerialSevenSegment _serialSevenSegment;
	BoksklokConfig bkCFG;
};

#endif