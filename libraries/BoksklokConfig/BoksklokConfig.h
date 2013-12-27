
#ifndef BoksklokConfig_h
#define BoksklokConfig_h

#include "Arduino.h"
#include <Countdown.h>

class BoksklokConfig
{
  public:
    BoksklokConfig();
	void set(int programm);
	Countdown getRestCountdown();
	Countdown getActiveCountdown();
  private:
	Countdown _active;
	Countdown _rest;
};

#endif