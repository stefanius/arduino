/*
Timings uit mail van Jaap
- 1 - 60 : 60 ( rondje van 1 minuut / 1 minuut pauze)

- 2 - 120 : 60 ( rondje van 2 minuten / 1 minuut pauze)

- 3 - 180 : 60 ( rondje van 3 minuten / 1 minuut pauze)

- 4 - 45 : 45 seconde

- 5 - 30 : 30 "

- 6 - 20 : 20 "

- 7 - 15 : 15 "

- 8 - 10 : 10 "

- 9 - 5 : 5 "
*/

#include "Arduino.h"
#include "BoksklokConfig.h"
#include <Countdown.h>
#include <SerialSevenSegment.h>

BoksklokConfig::BoksklokConfig()
{

}

void BoksklokConfig::set(int programm)
{
   //Countdown(mins, secs);
   if(programm==1){
		_active.set(1,0);
		_rest.set(1,0);   
   }else if(programm==2){
		_active.set(2,0);
		_rest.set(1,0);   
   }else if(programm==3){
		_active.set(3,0);
		_rest.set(1,0);   
   }else if(programm==4){
		_active.set(0,45);
		_rest.set(0,45);   
   }else if(programm==5){
		_active.set(0,30);
		_rest.set(0,30);   
   }else if(programm==6){
		_active.set(0,20);
		_rest.set(0,20);   
   }else if(programm==7){
		_active.set(0,15);
		_rest.set(0,15);   
   }else if(programm==8){
		_active.set(0,10);
		_rest.set(0,10);   
   }else if(programm==9){
		_active.set(0,5);
		_rest.set(0,5);   
   }else if(programm==10){
		_active.set(0,20);
		_rest.set(0,15);   
   }else if(programm==11){
		_active.set(0,30);
		_rest.set(0,15);   
   }else if(programm==12){
		_active.set(0,45);
		_rest.set(0,15);   
   }else if(programm==13){
		_active.set(1,0);
		_rest.set(0,15);   
   }else if(programm==14){
		_active.set(1,30);
		_rest.set(0,15);   
   }else if(programm==15){
		_active.set(2,0);
		_rest.set(0,15);   
   }else if(programm==16){
		_active.set(3,0);
		_rest.set(0,15);   
   }else if(programm==17){
		_active.set(0,20);
		_rest.set(0,10);   
   }else if(programm==18){
		_active.set(0,30);
		_rest.set(0,10);   
   }else if(programm==19){
		_active.set(0,45);
		_rest.set(0,10);   
   }else if(programm==20){
		_active.set(1,0);
		_rest.set(0,10);   
   }else if(programm==21){
		_active.set(1,30);
		_rest.set(0,10);   
   }else if(programm==22){
		_active.set(2,0);
		_rest.set(0,10);   
   }else if(programm==23){
		_active.set(0,5);
		_rest.set(0,5);   
   }else if(programm==24){
		_active.set(0,5);
		_rest.set(0,5);   
   }else if(programm==25){
		_active.set(0,5);
		_rest.set(0,5);   

   }
}
Countdown BoksklokConfig::getRestCountdown()
{
	return _rest;
}
Countdown BoksklokConfig::getActiveCountdown()
{
	return _active;
}