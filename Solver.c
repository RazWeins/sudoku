/*
 * Solver.c
 *
 *  Created on: 11 במאי 2018
 *      Author: beniz
 */

#include "Solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SPBufferset.h"

void printBoard(Cell** table, int blockRowSize, int blockColSize){
	int i, j;
	int boardColSize = blockColSize * blockRowSize;
	int boardRowSize = boardColSize;
	char strNonFixed[3];
	char strFixed[3];
	char strInt[2];
	int currentNum;

	for(i = 0; i < boardRowSize; i++){
		if(i % blockRowSize == 0){
			printf("%s", "----------------------------------\n");
		}
		for(j = 0; j < boardColSize; j++){
			strNonFixed[0] = ' ';
			strNonFixed[1] = '\0';
			strFixed[0] = '.';
			strFixed[1] = '\0';
			currentNum = table[i][j].currentNum;
			if(j % blockColSize == 0){
				printf("%s", "| ");
			}
			if(currentNum == 0){
				printf("%c", ' ');
			}
			if(table[i][j].fixed == 1){
				sprintf(strInt, "%d", currentNum);
				strcat(strFixed, strInt);
				printf("%s", strFixed);
			}
			if((table[i][j].fixed == 0) && (currentNum != 0)){
				sprintf(strInt, "%d", currentNum);
				strcat(strNonFixed, strInt);
				printf("%s", strNonFixed);
			}
			if(j == boardColSize - 1){
				printf("%s", " |");
			}
			printf("%s", " ");
		}
		printf("%s", "\n");
	}
	printf("%s", "----------------------------------\n");
}

/* resets cell num to 0 */
void resetCell(Cell** table, int cellRow, int cellCol){
	int i;
	table[cellRow][cellCol].currentNum = 0;

	for (i = 0; i < 9; i++) {/* initializes prevNums as not used nums*/
		table[cellRow][cellCol].prevNums[i] = 0;
	}

}
/* initializes board iwth zeros */
void boardInit(Cell** table, int boardRow, int boardCol){
	int i, j, k;
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){

			for (k = 0; k < 9; k++) {/* initializes prevNums as not used nums*/
				table[i][j].prevNums[k] = 0;
			}

			table[i][j].currentNum = 0;
			table[i][j].fixed = 0;
			table[i][j].limit = 9;

		}
	}
}

/* updates a cell with a valid numbers */
void updateCell(Cell** table, int numIndex, int cellRow, int cellCol){

	int num;
	num = table[cellRow][cellCol].validNums[numIndex];
	table[cellRow][cellCol].currentNum = num;
	table[cellRow][cellCol].prevNums[num - 1] = 1;
}

/* checks if a given number is in a specific row */
int rowCheck(Cell** table, int num, int cellRow , int blockRowSize, int blockColSize){
	int i, numCompare;
	int rowSize = blockRowSize * blockColSize;
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

/* checks if a given number is in a specific column */
int colCheck(Cell** table, int num,  int cellCol, int blockRowSize, int blockColSize){
	int i, numCompare;
	int colSize = blockRowSize * blockColSize;
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

/* gets the current block last column */
int getcurrentblockCol(int cellCol, int blockRowSize, int blockColSize){
	int boardSize = blockRowSize * blockColSize;
	int i = blockColSize - 1;
	float calcPos = 0;/* calculates relation between block end and cell position */
	while(i <= boardSize){
		calcPos = cellCol / (float) i;
		if(calcPos <= 1.0){
			return i;
		}
		i += blockColSize;
	}
	return -1;
}

/* gets the current block last row */
int getcurrentblockRow(int cellRow, int blockRowSize, int blockColSize){
	int boardSize = blockRowSize * blockColSize;
	int i = blockRowSize - 1;
	float calcPos = 0;/* calculates relation between block end and cell position */
	while(i <= boardSize){
		calcPos = cellRow / (float) i;
		if(calcPos <= 1.0){
			return i;
		}
		i += blockRowSize;
	}
	return -1;
}

/* checks if a given number is in a specific block */
int blockCheck(Cell** table,int numToCheck , int cellRow, int cellCol, int blockRowSize, int blockColSize){
	int currentNum;
	int i,j;
	int currentblockRow, currentblockCol;
	int minBlockLimitRow, minBlockLimitCol;
	currentblockRow = getcurrentblockRow(cellRow, blockRowSize, blockColSize) + 1;
	currentblockCol = getcurrentblockCol(cellCol, blockRowSize, blockColSize) + 1;
	minBlockLimitRow = currentblockRow - blockRowSize;
	minBlockLimitCol = currentblockCol - blockColSize;
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

/* checks if a number is a valid assignment by both row, column and block */
int validAssignment(Cell** table, int numToCheck, int cellRow, int cellCol, int blockRowSize, int blockColSize){
	int temp = 0;

	temp = rowCheck(table, numToCheck, cellRow, blockRowSize, blockColSize);
	if(temp < 0){
		return -1;
	}
	temp = colCheck(table, numToCheck, cellCol, blockRowSize, blockColSize);
	if(temp < 0){
		return -1;
	}
	temp = blockCheck(table, numToCheck, cellRow, cellCol, blockRowSize, blockColSize);
	if(temp < 0){
		return -1;
	}
	return 0;
}

/* check which numbers are available besides the current number
 * because we chose already this number and it was'nt good so
 * we should'nt try it again */
void availableNumbers(Cell** table, int cellRow, int cellCol, int blockRowSize, int blockColSize){
	int prevNumFlag;
	int counter = 0;/* counts the amount of valid numbers*/
	int num;
	for(num = 1; num < 10; num++){
		prevNumFlag = table[cellRow][cellCol].prevNums[num - 1];
		if(prevNumFlag == 0){/* checks if num was previously used */
			if(validAssignment(table, num, cellRow, cellCol, blockRowSize, blockColSize) == 0){/* value is 0 if num is a valid assignment*/
				table[cellRow][cellCol].validNums[counter] = num;
				counter++;
			}
		}
	}
	table[cellRow][cellCol].limit = counter;
}

/* random backtrack algorithm */
int rndBacktrack(Cell** table, int cellRow, int cellCol, int blockRowSize, int blockColSize, int boardSize){
	int limit;
	int rndIndex;
	int x;

	availableNumbers(table, cellRow, cellCol, blockRowSize, blockColSize);
	limit = table[cellRow][cellCol].limit;

	if(limit == 0){
		resetCell(table, cellRow, cellCol);
		return 0; /* got stuck need to trackback */
	}

	while(limit != 0) { /* keep looping through valid numbers */
		availableNumbers(table, cellRow, cellCol, blockRowSize, blockColSize);
		limit = table[cellRow][cellCol].limit;
		if(limit == 0){
			resetCell(table, cellRow, cellCol);
			return 0;
		}
		if( limit == 1 ){
			rndIndex = 0;
		}else{
			rndIndex = (rand() % limit);
		}
		updateCell(table, rndIndex, cellRow, cellCol);
		if(cellCol < boardSize - 1){
			x = rndBacktrack(table, cellRow, cellCol + 1, blockRowSize, blockColSize, boardSize);
			if(x == -1){
				return -1;
			}
		}else if(cellRow < boardSize - 1){
			x = rndBacktrack(table, cellRow + 1, 0, blockRowSize, blockColSize, boardSize);
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

/* wrapper for the random backtrack algorithm */
int rndBacktrackWrap(Cell** table, int blockRowSize, int blockColSize){

	int boardSize = blockRowSize * blockColSize;
	return rndBacktrack(table, 0, 0, blockRowSize, blockColSize, boardSize);
}


