/*
 * SimpleLedMatrixMultiplex - Led Multiplex Library
 * (c) sgrootveld@gmail.com - dec. 2013
 * sgrootveld@gmail.com
 */

#include "SimpleLedMatrixMultiplex.h"

SimpleLedMatrixMultiplex::SimpleLedMatrixMultiplex()
{
   _multiplex_delay = 5;
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

	  }
	  delay(_multiplex_delay);
	  digitalWrite(_cols[thiscol], HIGH);
	}

	digitalWrite(_rows[thisrow], LOW);
	
  }
}

void SimpleLedMatrixMultiplex::draw(int **pattern, int duration)
{
	for(int i =0; i < duration; i++){
		draw(pattern);
	}
}
void SimpleLedMatrixMultiplex::set_multiplex_delay(int delay)
{
	_multiplex_delay = delay;
}

int** SimpleLedMatrixMultiplex::retrieve_grid()
{
	return grid;
}

int** SimpleLedMatrixMultiplex::retrieve_clear_pattern()
{
	for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
		for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
			grid[thisrow][thiscol] = LOW;
		}
	}
	return grid;
}

int** SimpleLedMatrixMultiplex::retrieve_center_pattern()
{
	int center_row = 0;
	int center_col = 0;

	if((_no_rows % 2) == 1){ //odd value for rows
		if(_no_rows > 1){
			center_row = ((_no_rows+1)/2)-1;
		}
	}

	if((_no_cols % 2) == 1){ //odd value for cols
		if(_no_cols > 1){
			center_col = ((_no_cols+1)/2)-1;
		}
	}

	grid[center_row][center_col] = HIGH;
	return grid;
}

int** SimpleLedMatrixMultiplex::retrieve_pattern(SimpleLedMatrixMultiplex::Patterns pattern)
{
	grid= retrieve_clear_pattern();
	if(pattern == SimpleLedMatrixMultiplex::FILLED_SQUARE){
		  for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
			for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
				grid[thisrow][thiscol] = HIGH;
			}
		  }
	}else if(pattern == SimpleLedMatrixMultiplex::BORDER_ALL){
		  for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
			for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
				if(thisrow == 0 || thisrow == (_no_rows-1) ){
					grid[thisrow][thiscol] = HIGH;
				}else if(thiscol == 0 || thiscol == (_no_cols-1) ){
					grid[thisrow][thiscol] = HIGH;
				}

			}
		  }
	}else if(pattern == SimpleLedMatrixMultiplex::BORDER_TOP){

			for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
				grid[_no_rows-1][thiscol] = HIGH;
			}
	}else if(pattern == SimpleLedMatrixMultiplex::BORDER_BOTTOM){

			for (int thiscol = 0; thiscol < _no_cols; thiscol++) {
				grid[0][thiscol] = HIGH;
			}
	}else if(pattern == SimpleLedMatrixMultiplex::BORDER_LEFT){

			for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
				grid[thisrow][0] = HIGH;
			}
	}else if(pattern == SimpleLedMatrixMultiplex::BORDER_RIGHT){

			for (int thisrow = 0; thisrow < _no_rows; thisrow++) {
				grid[thisrow][_no_cols-1] = HIGH;
			}
	}else if(pattern == SimpleLedMatrixMultiplex::DIAG_A){
			int max = 0;
			if(_no_rows > _no_cols){
				max = _no_rows;
			}else{
				max = _no_cols;
			}

			for (int i = 0; i < max; i++) {
				grid[i][i] = HIGH;

				if(i >= _no_rows || i >= _no_cols){
					break;
				}
			}
	}else if(pattern == SimpleLedMatrixMultiplex::DIAG_B){
			grid[2][0] = HIGH;
			grid[1][1] = HIGH;
			grid[0][2] = HIGH;
	}else if(pattern == SimpleLedMatrixMultiplex::CENTER){
			grid= retrieve_center_pattern();
	}



	return grid;
}
