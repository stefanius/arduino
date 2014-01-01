/*
 * SimpleLedMatrixMultiplex - Led Multiplex Library
 * (c) sgrootveld@gmail.com - dec. 2013
 * sgrootveld@gmail.com
 */


#include "SimpleLedMatrixMultiplex.h"

SimpleLedMatrixMultiplex::SimpleLedMatrixMultiplex()
{
  _no_rows = 3;
  _no_cols = 3;
  grid = new int*[_no_rows]; // dynamic array (size 10) of pointers to int

  for (int i = 0; i < _no_rows; ++i) {
	  grid[i] = new int[_no_cols];
  }
}

void SimpleLedMatrixMultiplex::draw(int **pattern)
{
  for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
	for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
		int *rowPattern = pattern[thisrow];
	  if(rowPattern[thiscol] == HIGH){
		 digitalWrite(_rows[thisrow], HIGH);
		 digitalWrite(_cols[thiscol], LOW);
		 delay(5);
	  }

	  digitalWrite(_cols[thiscol], HIGH);
	}

	digitalWrite(_rows[thisrow], LOW);
	
  }
}

int** SimpleLedMatrixMultiplex::retrieve_grid()
{
	return grid;
}
