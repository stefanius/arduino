
#include "Boksklok.h"

Boksklok::Boksklok(SerialSevenSegment serialSevenSegment, int pinGreenLight, int pinRedLight, int pinYellowLight, int pinBuzzerA, int pinBuzzerB)
{
	_serialSevenSegment = serialSevenSegment;
	_pinGreenLight=pinGreenLight;
	_pinRedLight=pinRedLight;
	_pinYellowLight=pinYellowLight;
	_pinBuzzerA=pinBuzzerA;
	_pinBuzzerB=pinBuzzerB;
	
	pinMode(_pinGreenLight, OUTPUT); 
	pinMode(_pinRedLight, OUTPUT); 
	pinMode(_pinYellowLight, OUTPUT); 
	pinMode(_pinBuzzerA, OUTPUT); 
	pinMode(_pinBuzzerB, OUTPUT);
}

void Boksklok::set(int programm)
{
	bkCFG.set(programm);
	_rest = bkCFG.getRestCountdown();
	_active = bkCFG.getActiveCountdown();
}

void Boksklok::wait(int seconds)
{
	seconds=seconds%60;
	setVisualInRest();
	Countdown pause(0,seconds);
	
	while(pause.decreaseToZero()==false){
	  _serialSevenSegment.writeClock(pause.getMinutes(),pause.getSeconds());
	  delay(1000);
	} 	
	setVisualInActive();
}

void Boksklok::setVisualInRest()
{
	_serialSevenSegment.toggleAposOn();
	digitalWrite(_pinRedLight, HIGH);
	digitalWrite(_pinGreenLight, LOW);
	delay(200);
}

void Boksklok::setVisualInActive()
{
	_serialSevenSegment.toggleAposOff();
	digitalWrite(_pinRedLight, LOW);
	digitalWrite(_pinGreenLight, HIGH);
	delay(200);
}

void Boksklok::buzzer(int buzztime)
{
	digitalWrite(_pinBuzzerA, HIGH);
	digitalWrite(_pinBuzzerB, HIGH);
	digitalWrite(_pinYellowLight, HIGH);
	delay(buzztime);
	digitalWrite(_pinYellowLight, LOW);
	digitalWrite(_pinBuzzerA, LOW);	
	digitalWrite(_pinBuzzerB, LOW);
	delay(5);
}

void Boksklok::toggleYellowLedOn()
{
	digitalWrite(_pinYellowLight, HIGH);
}

void Boksklok::toggleYellowLedOff()
{
	digitalWrite(_pinYellowLight, LOW);
}

void Boksklok::toggleGreenLedOn()
{
	digitalWrite(_pinGreenLight, HIGH);
}

void Boksklok::toggleGreenLedOff()
{
	digitalWrite(_pinGreenLight, LOW);
}

void Boksklok::start()
{
	buzzer(1000);
	setVisualInActive();
	while(_active.decreaseToZero()==false){
		_serialSevenSegment.writeClock(_active.getMinutes(),_active.getSeconds());
		delay(1000); 	
	}
	_serialSevenSegment.writeClock(_active.getMinutes(),_active.getSeconds());
	delay(1000);
	
	buzzer(1000);
	setVisualInRest();
	while(_rest.decreaseToZero()==false){
		
		_serialSevenSegment.writeClock(_rest.getMinutes(),_rest.getSeconds());
		delay(1000); 	
	}
	_serialSevenSegment.writeClock(_rest.getMinutes(),_rest.getSeconds());
	delay(1000); 		
	_rest = bkCFG.getRestCountdown();
	_active = bkCFG.getActiveCountdown();	
	
}