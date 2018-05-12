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

void createBoards(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize, int amountOfHints){
	int success;
	boardInit(gameBoard, blockRowSize, blockColSize);
	boardInit(solvedBoard, blockRowSize, blockColSize);
	rndBacktrackWrap(solvedBoard, blockRowSize, blockColSize);
	setHints(solvedBoard, amountOfHints, blockRowSize, blockColSize);
	createGameBoard(gameBoard, solvedBoard, blockRowSize, blockColSize);
	printBoard(gameBoard, blockRowSize, blockColSize);
	success = dtrBacktrackWrap(gameBoard, blockRowSize, blockColSize);
	printf("%s", "\n");
	if(success == -1){
		printf("%s", "there's a solution");
	}else{
		printf("%s", "there's no solution");
	}
	printf("%s", "\n");
	printBoard(gameBoard, blockRowSize, blockColSize);

}

/*char* getStatus(){  prints current status of the board
*	return 0;
*}
*
*int isValid(){ returns 0-invalid 1-valid
*	return 0;
*}
*
*char hint(int X, int Y){ returns a hint for cell X,Y
*	return 'a';
*}
*
*int setCell(int X, int Y, int Z){ sets cell X,Y with value Z
*	return 0;
*}
*/

