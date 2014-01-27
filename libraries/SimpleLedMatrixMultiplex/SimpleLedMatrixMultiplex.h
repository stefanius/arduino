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
	typedef enum Patterns {
								FILLED_SQUARE,
								BORDER_ALL,
								BORDER_TOP,
								BORDER_BOTTOM,
								BORDER_LEFT,
								BORDER_RIGHT,
								CENTER,
								CROSS,
								DIAG_A,
								DIAG_B,
								EMPTY
							};

	SimpleLedMatrixMultiplex();
	void draw(int **pattern);
	void draw(int **pattern, int duration);
	void set_multiplex_delay(int delay);
	int** retrieve_grid();
	int** retrieve_clear_pattern();
	int** retrieve_center_pattern();
	int** retrieve_pattern(SimpleLedMatrixMultiplex::Patterns pattern);

  private:
	int **grid;
	int _no_rows;
	int _no_cols;
	int _multiplex_delay;
	int _rows[3]={2,3,4};
	int _cols[3]={8,9,10};
};

#endif
