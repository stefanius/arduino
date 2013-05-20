
#ifndef Countdown_h
#define Countdown_h

#include "Arduino.h"

class Countdown
{
  public:
    Countdown(int mins, int secs);
    void increase();
    void decrease();
	int getMinutes();
	int getSeconds();
  private:
    int _mins;
	int _secs;
};

#endif