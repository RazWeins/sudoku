/*
 * gameUnitTest.c
 *
 *  Created on: 19 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "Game.h"
#include "MainAux.h"
#include "def.h"
#include "Cell.h"

void isInit(Cell** board){
	int i,j,k;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int boardCol = boardRow;

	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){

			for (k = 0; k < 9; k++) {
				if(board[i][j].prevNums[k] != 0)
					printf("%s","ERROR: isInit line 30");
			}
			if(board[i][j].currentNum != 0 || board[i][j].fixed != 0 || board[i][j].isInput != 0 || board[i][j].limit != 9){
				printf("%s","ERROR: isInit line 33");
			}
		}
	}
}

void test(){
	Cell** gameBoard = NULL;
	Cell** solvedBoard = NULL;
	Cell** tempBoard = NULL;
	int i, j;

	gameBoard = setAllocatedMem();
	solvedBoard = setAllocatedMem();
	tempBoard = setAllocatedMem();

	boardInit(gameBoard);
	boardInit(solvedBoard);
	boardInit(tempBoard);

	isInit(gameBoard);
	isInit(solvedBoard);
	isInit(tempBoard);

	for(i = 0; i < 81 ; i++){
		puzzleGeneration(gameBoard, solvedBoard, tempBoard,i);
	}

	for(i = 0; i < 81 ; i++){
		for(j = 0; j < 81 ; j++){
			/*setCell(ta) */
		}
		puzzleGeneration(gameBoard, solvedBoard, tempBoard,i);
	}



}

