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
  
  sm.set_multiplex_delay(1);
  board = sm.retrieve_grid();
}

// the loop routine runs over and over again forever:
void loop() {

  int duration = 250;
  
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::FILLED_SQUARE);
  sm.draw(board, duration);
  
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::BORDER_ALL);
  sm.draw(board, duration);
   
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::BORDER_TOP);
  sm.draw(board, duration);
   
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::BORDER_BOTTOM);
  sm.draw(board, duration);
  
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::BORDER_LEFT);
  sm.draw(board, duration);
 
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::BORDER_RIGHT);
  sm.draw(board, duration);
  
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::DIAG_A);
  sm.draw(board, duration);
   
  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::DIAG_B);
  sm.draw(board, duration);

  board = sm.retrieve_pattern(SimpleLedMatrixMultiplex::CENTER);
  sm.draw(board, duration);
 
  board = sm.retrieve_clear_pattern();
  sm.draw(board, duration); 
}


