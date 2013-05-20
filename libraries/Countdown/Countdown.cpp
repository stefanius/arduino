/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Countdown.h"

Countdown::Countdown(int mins, int secs)
{
  _mins = mins;
  _secs = secs;
}

void Countdown::increase()
{
	if(_secs < 60){
		_secs++;
	}else{
		_mins++;
		_secs=0;
	}
}
void Countdown::decrease()
{
	if(_secs > 0){
		_secs--;
		}else{
		_secs=59;
		_mins--;
	}
}
int Countdown::getMinutes()
{
	return _mins;
}
int Countdown::getSeconds()
{
	return _secs;
}