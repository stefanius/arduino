
#include "BoksklokSPI.h"

Boksklok::Boksklok(SerialSevenSegment &serialSevenSegment)
{
	_serialSevenSegment = &serialSevenSegment;
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
	  _serialSevenSegment->writeClock(pause.getMinutes(),pause.getSeconds());
	  delay(1000);
	} 	
	setVisualInActive();
}

void Boksklok::setVisualInRest()
{
	_serialSevenSegment->toggleAposOn();
	//digitalWrite(13, HIGH);
	//digitalWrite(12, LOW);
	delay(200);
}

void Boksklok::setVisualInActive()
{
	_serialSevenSegment->toggleAposOff();
	//digitalWrite(13, LOW);
	//digitalWrite(12, HIGH);
	delay(200);
}

void Boksklok::start()
{
	setVisualInActive();
	while(_active.decreaseToZero()==false){
		_serialSevenSegment->writeClock(_active.getMinutes(),_active.getSeconds());
		delay(1000); 	
	}
	_serialSevenSegment->writeClock(_active.getMinutes(),_active.getSeconds());
	delay(1000);
	
	setVisualInRest();
	while(_rest.decreaseToZero()==false){
		
		_serialSevenSegment->writeClock(_rest.getMinutes(),_rest.getSeconds());
		delay(1000); 	
	}
	_serialSevenSegment->writeClock(_rest.getMinutes(),_rest.getSeconds());
	delay(1000); 		
	_rest = bkCFG.getRestCountdown();
	_active = bkCFG.getActiveCountdown();	
	
}