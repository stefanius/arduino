/*
 * SimpleLedMatrixMultiplex - Led Multiplex Library
 * (c) sgrootveld@gmail.com - dec. 2013
 * sgrootveld@gmail.com
 */

#ifndef SimpleLedMatrixMultiplex_h
#define SimpleLedMatrixMultiplex_h

#include "Arduino.h"

class SimpleLedMatrixMultiplex
{
  public:
	SimpleLedMatrixMultiplex();
	void draw(int **pattern);
	int** retrieve_grid();

  private:
	int **grid;
	int _no_rows;
	int _no_cols;
	int _rows[3]={2,3,4};
	int _cols[3]={8,9,10};
};

#endif
