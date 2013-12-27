
#ifndef Countdown_h
#define Countdown_h

#include "Arduino.h"

class Countdown
{
  public:
    Countdown(int mins, int secs);
	Countdown();
	void set(int mins, int secs);
    void increase();
    void decrease();
	bool decreaseToZero();
	int getMinutes();
	int getSeconds();
  private:
    int _mins;
	int _secs;
};

#endif