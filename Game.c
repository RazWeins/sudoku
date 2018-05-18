/*
 * Game.c
 *
 *  Created on: 7 May 2018
 *      Author: Raz
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "Game.h"
#include "Solver.h"

/* initializes board with zeros */
void boardInit(Cell** table, int blockRowSize, int blockColSize){
	int i, j, k;
	int boardRow = blockRowSize * blockColSize;
	int boardCol = boardRow;
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){

			for (k = 0; k < 9; k++) {/* initializes prevNums as not used nums*/
				table[i][j].prevNums[k] = 0;
			}

			table[i][j].currentNum = 0;
			table[i][j].fixed = 0;
			table[i][j].isInput = 0;
			table[i][j].limit = 9;

		}
	}
}

void setHints(Cell** table, int amountOfHints, int blockRowSize, int blockColSize){
	int fixedCounter = 0;
	int rowIndex = 0;
	int colIndex = 0;
	int boardColSize = blockColSize * blockRowSize;
	int boardRowSize = boardColSize;
	while(fixedCounter < amountOfHints){
		rowIndex = (rand() % boardRowSize);
		colIndex = (rand() % boardColSize);
		if(table[rowIndex][colIndex].fixed == 0){
			table[rowIndex][colIndex].fixed = 1;
			fixedCounter++;
		}
	}
}

/* making the board ready for a game, setting fixed numbers */
void createGameBoard(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize){
	int i, j;
	int isFixed;
	int currentNum;
	int boardRow = blockRowSize * blockColSize;
	int boardCol = boardRow;
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			isFixed = solvedBoard[i][j].fixed;
			if(isFixed == 1){
				currentNum = solvedBoard[i][j].currentNum;
				gameBoard[i][j].fixed = 1;
				gameBoard[i][j].currentNum = currentNum;
			}
		}
	}
}

void initGame(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize, int amountOfHints){
	boardInit(gameBoard, blockRowSize, blockColSize);
	boardInit(solvedBoard, blockRowSize, blockColSize);
	rndBacktrackWrap(solvedBoard, blockRowSize, blockColSize);
	setHints(solvedBoard, amountOfHints, blockRowSize, blockColSize);
	createGameBoard(gameBoard, solvedBoard, blockRowSize, blockColSize);
}

int isSolved(Cell** table, int blockRowSize, int blockColSize){
	int i, j;
	int boardRow = blockRowSize * blockColSize;
	int boardCol = boardRow;

	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			if(table[i][j].currentNum == 0){
				return 0;
			}
		}
	}
	return 1;
}

/* updates a cell with a valid numbers, returns 1 if board is solved else returns 0 */
int setCell(Cell** table, int cellRow, int cellCol, int cellValue, int blockRowSize, int blockColSize){
	int fixedFlag = table[cellRow - 1][cellCol - 1].fixed;
	if(!fixedFlag){
		if(cellValue == 0){
			table[cellRow - 1][cellCol - 1].currentNum = 0;
			table[cellRow - 1][cellCol - 1].isInput = 0;
			return 0;
		}else{
			if(validAssignment(table, cellValue, cellRow - 1, cellCol - 1, blockRowSize, blockColSize) == 0){
				table[cellRow - 1][cellCol - 1].currentNum = cellValue;
				table[cellRow - 1][cellCol - 1].isInput = 1;
				printBoard(table, blockRowSize, blockColSize);
				if(isSolved(table, blockRowSize, blockColSize)){
					printf("%s","Puzzle solved successfully\n");
					return 1;
				}else{
					return 0;
				}
			}else{
				printf("%s","Error: value is invalid\n");
				return 0;
			}
		}
	}else{
		printf("%s","Error: cell is fixed\n");
		return 0;
	}
	return 0;
}

/* returns hint at (cellRow,cellCol). table is solvedBoard */
void hintCell(Cell** table, int cellRow, int cellCol){
	int hint = table[cellRow - 1][cellCol - 1].currentNum;

	printf("%s", "Hint: set cell to ");
	printf("%d", hint);
	printf("%s", "\n");
}

/* copies the actual values of one board to another board */
void copyBoard(Cell** dstBoard, Cell** srcBoard, int blockRowSize, int blockColSize){
	int i, j;
	int boardRow = blockRowSize * blockColSize;
	int boardCol = boardRow;

	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			dstBoard[i][j].currentNum = srcBoard[i][j].currentNum;
			dstBoard[i][j].fixed = srcBoard[i][j].fixed;
			dstBoard[i][j].isInput = srcBoard[i][j].isInput;
		}
	}
}

void validateBoard(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard,int blockRowSize, int blockColSize){
	int solveFlag;

	boardInit(tempBoard, blockRowSize, blockColSize);

	copyBoard(tempBoard, gameBoard, blockRowSize, blockColSize);

	solveFlag = dtrBacktrackWrap(tempBoard, blockRowSize, blockColSize);
	if(solveFlag == 0){
		printf("%s","Validation failed: board is unsolvable\n");
	}else{
		copyBoard(solvedBoard, tempBoard, blockRowSize, blockColSize);
		printf("%s","Validation passed: board is solvable\n");
	}
}

void exitGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard){
	free(gameBoard);
	free(solvedBoard);
	free(tempBoard);

	printf("%s","Exiting…\n");
}
