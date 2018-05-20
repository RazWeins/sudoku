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
#include "def.h"

void printBoard(Cell** table){
	int i, j;
	int boardColSize = BLOCK_COL_SIZE * BLOCK_ROW_SIZE;
	int boardRowSize = boardColSize;
	char strNonFixed[3];
	char strFixed[3];
	char strInt[2];
	int currentNum;

	for(i = 0; i < boardRowSize; i++){
		if(i % BLOCK_ROW_SIZE == 0){
			printf("%s", "----------------------------------\n");
		}
		for(j = 0; j < boardColSize; j++){
			strNonFixed[0] = ' ';
			strNonFixed[1] = '\0';
			strFixed[0] = '.';
			strFixed[1] = '\0';
			currentNum = table[i][j].currentNum;
			if(j % BLOCK_COL_SIZE == 0){
				printf("%s", "| ");
			}
			if(currentNum == 0){
				printf("%s", "  ");
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


void boardInit(Cell** table){
	int i, j, k;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
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

/*
 * Function:  setHints
 * --------------------
 *  setting random cells as hints by making them fixed
 *
 *  amountOfHints: number of hints wanted
 *
 */
void setHints(Cell** table, int amountOfHints){
	int fixedCounter = 0;
	int rowIndex = 0;
	int colIndex = 0;
	int boardColSize = BLOCK_COL_SIZE * BLOCK_ROW_SIZE;
	int boardRowSize = boardColSize;
	while(fixedCounter < amountOfHints){
		colIndex = (rand() % boardColSize);
		rowIndex = (rand() % boardRowSize);
		if(table[rowIndex][colIndex].fixed == 0){
			table[rowIndex][colIndex].fixed = 1;
			fixedCounter++;
		}
	}
}

/*
 * Function:  createGameBoard
 * --------------------
 *  copies the solvedboard's fixed cells numbers to gameboard
 *
 *  gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *
 */
void createGameBoard(Cell** gameBoard, Cell** solvedBoard){
	int i, j;
	int isFixed;
	int currentNum;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
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

void puzzleGeneration(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard, int amountOfHints){
	boardInit(gameBoard);
	boardInit(solvedBoard);
	boardInit(tempBoard);
	sudokuGenerator(solvedBoard);
	setHints(solvedBoard, amountOfHints);
	createGameBoard(gameBoard, solvedBoard);
}

/*
 * Function:  isSolved
 * --------------------
 *  checks if all cells has a number different from zero,
 *   if yes it means the board is solved
 *
 *  table: 2d array holding a sudoku board
 *
 *  returns: 1 if the board is solved, 0 if the board is not solved
 *
 */
int isSolved(Cell** table){
	int i, j;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
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


int setCell(Cell** table, int cellRow, int cellCol, int cellValue){
	int fixedFlag = table[cellRow - 1][cellCol - 1].fixed;
	if(!fixedFlag){
		if(cellValue == 0){
			table[cellRow - 1][cellCol - 1].currentNum = 0;
			table[cellRow - 1][cellCol - 1].isInput = 0;
			return 0;
		}else{
			if(validAssignment(table, cellValue, cellRow - 1, cellCol - 1) == 0){
				table[cellRow - 1][cellCol - 1].currentNum = cellValue;
				table[cellRow - 1][cellCol - 1].isInput = 1;
				if(isSolved(table)){
					printf("%s","Puzzle solved successfully\n");
					return 1;
				}else{
					printBoard(table);
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


void hintCell(Cell** solvedBoard, int cellRow, int cellCol){
	int hint = solvedBoard[cellRow - 1][cellCol - 1].currentNum;

	printf("%s", "Hint: set cell to ");
	printf("%d", hint);
	printf("%s", "\n");
}

/*
 * Function:  copyBoard
 * --------------------
 * copies srcBoard board to dstBoard
 *
 *  dstBoard: 2d array holding a sudoku board, copy destination
 *  srcBoard: 2d array holding a sudoku board, copy source
 *
 */
void copyBoard(Cell** dstBoard, Cell** srcBoard){
	int i, j;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int boardCol = boardRow;

	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			dstBoard[i][j].currentNum = srcBoard[i][j].currentNum;
			dstBoard[i][j].fixed = srcBoard[i][j].fixed;
			dstBoard[i][j].isInput = srcBoard[i][j].isInput;
		}
	}
}

void validateBoard(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard){
	int solveFlag = 0;
	boardInit(tempBoard);
	copyBoard(tempBoard, gameBoard);
	solveFlag = sudokuSolver(tempBoard);

	if(solveFlag == 0){
		printf("%s","Validation failed: board is unsolvable\n");
	}else{
		boardInit(solvedBoard);
		copyBoard(solvedBoard, tempBoard);
		printf("%s","Validation passed: board is solvable\n");
	}
}

void exitGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard){
	int boardRowSize = BLOCK_COL_SIZE * BLOCK_ROW_SIZE;
	int i;
	for (i = 0; i < boardRowSize; i++) {
		free(tempBoard[i]);
	}
	for (i = 0; i < boardRowSize; i++) {
		free(solvedBoard[i]);
	}
	for (i = 0; i < boardRowSize; i++) {
		free(gameBoard[i]);
	}
	free(tempBoard);
	free(solvedBoard);
	free(gameBoard);
	printf("%s","Exiting...\n");
	exit(0);
}
