/*
 * Solver.c
 *
 *  Created on: 11 ���� 2018
 *      Author: beniz
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Solver.h"
#include "def.h"


/*
 * Function:  resetCell
 * --------------------
 *  resets cell num to 0 and put 0 in array of the previous numbers it tried during backtracking
 *
 *  table: 2d array containing sudoku cells
 *	cellRow: row of cell to reset
 *	cellCol: column of cell to reset
 */
void resetCell(Cell** table, int cellRow, int cellCol){
	int i;
	table[cellRow][cellCol].currentNum = 0;

	for (i = 0; i < 9; i++) {/* initializes prevNums as not used nums*/
		table[cellRow][cellCol].prevNums[i] = 0;
	}

}

/*
 * Function:  updateCell
 * --------------------
 *  updates cell with a new number with one of it's valid numbers
 *
 *  table: 2d array containing sudoku cells
 *  numIndex: index of valid number from the cell valid numbers array
 *	cellRow: row of cell to reset
 *	cellCol: column of cell to reset
 */
void updateCell(Cell** table, int numIndex, int cellRow, int cellCol){

	int num;
	num = table[cellRow][cellCol].validNums[numIndex];
	table[cellRow][cellCol].currentNum = num;
	table[cellRow][cellCol].prevNums[num - 1] = 1;
}

/*
 * Function:  rowCheck
 * --------------------
 *  checks if a given number is in a specific row
 *
 *  table: 2d array containing sudoku cells
 *  num: number to check
 *	cellRow: row to check
 *
 *	returns: -1 if number already appears in row, else it returns 0
 */
int rowCheck(Cell** table, int num, int cellRow){
	int i, numCompare;
	int rowSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	for(i = 0; i < rowSize; i++){
		numCompare = table[cellRow][i].currentNum;
		if(numCompare != 0){
			if(numCompare == num){
				return -1;
			}
		}
	}
	return 0;
}

/*
 * Function:  colCheck
 * --------------------
 *  checks if a given number is in a specific col
 *
 *  table: 2d array containing sudoku cells
 *  num: number to check
 *	cellCol: column to check
 *
 *	returns: -1 if number already appears in row, else it returns 0
 */
int colCheck(Cell** table, int num,  int cellCol){
	int i, numCompare;
	int colSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	for(i = 0; i < colSize; i++){
		numCompare = table[i][cellCol].currentNum;
		if(numCompare != 0){
			if(numCompare == num){
				return -1;
			}
		}
	}
	return 0;
}

/*
 * Function:  getcurrentblockCol
 * --------------------
 *  calculates the ending column of the block of the column cellCol
 *
 *	cellCol: column to check
 *
 *	returns: number of ending column of the block of the column cellCol
 */
int getcurrentblockCol(int cellCol){
	int boardSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int i = BLOCK_COL_SIZE - 1;
	float calcPos = 0;/* calculates relation between block end and cell position */
	while(i <= boardSize){
		calcPos = cellCol / (float) i;
		if(calcPos <= 1.0){
			return i;
		}
		i += BLOCK_COL_SIZE;
	}
	return -1;
}

/*
 * Function:  getcurrentblockRow
 * --------------------
 *  calculates the ending row of the block of the column cellRow
 *
 *	cellRow: row to check
 *
 *	returns: number of ending row of the block of the column cellRow
 */
int getcurrentblockRow(int cellRow){
	int boardSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int i = BLOCK_ROW_SIZE - 1;
	float calcPos = 0;/* calculates relation between block end and cell position */
	while(i <= boardSize){
		calcPos = cellRow / (float) i;
		if(calcPos <= 1.0){
			return i;
		}
		i += BLOCK_ROW_SIZE;
	}
	return -1;
}

/*
 * Function:  blockCheck
 * --------------------
 *  checks if numToCheck is in the block of the cell
 *  at column of cellCol and row of cellRow in table
 *
 *	table: 2d array containing sudoku cells
 *	numToCheck: number we want to check
 *	cellRow: cell's row
 *	cellCol: cells's column
 *
 *	returns: 0 numToCheck is not in the block,
 *			-1 numToCheck is in the block
 */
int blockCheck(Cell** table,int numToCheck , int cellRow, int cellCol){
	int currentNum;
	int i,j;
	int currentblockRow, currentblockCol;
	int minBlockLimitRow, minBlockLimitCol;
	currentblockRow = getcurrentblockRow(cellRow) + 1;
	currentblockCol = getcurrentblockCol(cellCol) + 1;
	minBlockLimitRow = currentblockRow - BLOCK_ROW_SIZE;
	minBlockLimitCol = currentblockCol - BLOCK_COL_SIZE;
	for(i = minBlockLimitRow; i < currentblockRow; i++){
		for(j = minBlockLimitCol; j < currentblockCol; j++){
			currentNum = table[i][j].currentNum;
			if(numToCheck == currentNum){
				return -1;
			}
		}
	}
	return 0;
}


int validAssignment(Cell** table, int numToCheck, int cellRow, int cellCol){
	int temp = 0;

	temp = rowCheck(table, numToCheck, cellRow);
	if(temp < 0){
		return -1;
	}
	temp = colCheck(table, numToCheck, cellCol);
	if(temp < 0){
		return -1;
	}
	temp = blockCheck(table, numToCheck, cellRow, cellCol);
	if(temp < 0){
		return -1;
	}
	return 0;
}

/*
 * Function:  availableNumbers
 * --------------------
 * 	checks which numbers are available to the cell
 * 	at column of cellCol and row of cellRow and updates
 * 	the validNums array with them and the limit field accordingly
 *
 *	table: 2d array containing sudoku cells
 *	cellRow: cell's row
 *	cellCol: cells's column
 *
 */
void availableNumbers(Cell** table, int cellRow, int cellCol){
	int prevNumFlag;
	int counter = 0;/* counts the amount of valid numbers*/
	int num;
	for(num = 1; num < 10; num++){
		prevNumFlag = table[cellRow][cellCol].prevNums[num - 1];
		if(prevNumFlag == 0){/* checks if num was previously used */
			if(validAssignment(table, num, cellRow, cellCol) == 0){/* value is 0 if num is a valid assignment*/
				table[cellRow][cellCol].validNums[counter] = num;
				counter++;
			}
		}
	}
	table[cellRow][cellCol].limit = counter;
}

/*
 * Function:  rndBacktrack
 * --------------------
 * 	random back tracking algorithm
 *
 *	table: 2d array containing sudoku cells
 *	cellRow: cell's row
 *	cellCol: cells's column
 *	boardSize: size of sudoku board
 *
 *	returns: -1 if generated board successfully,
 *			  0 if couldn't generate board successfully
 *
 */
int rndBacktrack(Cell** table, int cellRow, int cellCol, int boardSize){
	int limit;
	int rndIndex;
	int x;

	availableNumbers(table, cellRow, cellCol);
	limit = table[cellRow][cellCol].limit;

	if(limit == 0){
		resetCell(table, cellRow, cellCol);
		return 0; /* got stuck need to trackback */
	}

	while(limit != 0) { /* keep looping through valid numbers */
		availableNumbers(table, cellRow, cellCol);
		limit = table[cellRow][cellCol].limit;
		if(limit == 0){
			resetCell(table, cellRow, cellCol);
			return 0;
		}
		if( limit == 1 ){
			rndIndex = 0;
		}else{
			rndIndex = (rand()  % limit);
		}
		updateCell(table, rndIndex, cellRow, cellCol);
		if(cellCol < boardSize - 1){
			x = rndBacktrack(table, cellRow, cellCol + 1, boardSize);
			if(x == -1){
				return -1;
			}
		}else if(cellRow < boardSize - 1){
			x = rndBacktrack(table, cellRow + 1, 0, boardSize);
			if(x == -1){
				return -1;
			}
		}else{
			/* got to the last cell */
			return -1;
		}
	}
	return -1;
}


void sudokuGenerator(Cell** table){

	int boardSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	rndBacktrack(table, 0, 0, boardSize);
}

/*
 * Function:  dtrBacktrack
 * --------------------
 * 	deterministic back tracking algorithm
 *
 *	table: 2d array containing sudoku cells
 *	cellRow: cell's row
 *	cellCol: cells's column
 *	boardSize: size of sudoku board
 *
 *	returns: -1 if solved board successfully,
 *			  0 if couldn't solve board successfully
 *
 */
int dtrBacktrack(Cell** table, int cellRow, int cellCol, int boardSize){
	int limit;
	int numIndex;
	int x;

	if(table[cellRow][cellCol].fixed == 1 || table[cellRow][cellCol].isInput == 1){
		if(cellCol < boardSize - 1){
			x = dtrBacktrack(table, cellRow, cellCol + 1, boardSize);
			return x;
		}
		else if(cellRow < boardSize - 1){
			x = dtrBacktrack(table, cellRow + 1, 0, boardSize);
			return x;
		}else{
			return -1; /* got to last cell and it's fixed\input */
		}
	}else{
		availableNumbers(table, cellRow, cellCol);
		limit = table[cellRow][cellCol].limit;

		if(limit == 0){
			resetCell(table, cellRow, cellCol);
			return 0; /* got stuck need to trackback */
		}

		while(limit != 0) { /* keep looping through valid numbers */
			availableNumbers(table, cellRow, cellCol);
			limit = table[cellRow][cellCol].limit;
			if(limit == 0){
				resetCell(table, cellRow, cellCol);
				return 0;
			}
			numIndex = 0;
			updateCell(table, numIndex, cellRow, cellCol);
			if(cellCol < boardSize - 1){
				x = dtrBacktrack(table, cellRow, cellCol + 1, boardSize);
				if(x == -1){
					return -1;
				}
			}else if(cellRow < boardSize - 1){
				x = dtrBacktrack(table, cellRow + 1, 0, boardSize);
				if(x == -1){
					return -1;
				}
			}else{
				/* got to the last cell */
				return -1;
			}
		}
		return -1;
	}
 return -1;
}


int sudokuSolver(Cell** table){

	int boardSize = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	return dtrBacktrack(table, 0, 0, boardSize);
}
