#include <SimpleLedMatrixMultiplex.h>

int row[3] = {2,3,4};
int col[3] = {8,9,10};

SimpleLedMatrixMultiplex sm;
int **board;



void setup() {
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 3; thisPin++) {
    // initialize the output pins:
    pinMode(row[thisPin], OUTPUT); 
    pinMode(col[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);
    digitalWrite(row[thisPin], LOW);    
  }
  
  board = sm.retrieve_grid();
}

// the loop routine runs over and over again forever:
void loop() {

  board[2][0] = HIGH;
  board[2][1] = HIGH;
  board[2][2] = HIGH;
  sm.draw(board);  
  

}

