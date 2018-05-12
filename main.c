/*
 * main.c
 *
 *  Created on: 7 May 2018
 *      Author: Raz
 */
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"
#include "Parser.h"
#include "Solver.h"
#include "Cell.h"
#include "Game.h"

int main(){

	/* Declarations */
	char testArray[1024] = "set 2 3 4";
	int currentCommand[4] = {0,0,0,0};

	int blockRowSize = 3;
	int blockColSize = 3;
	int boardRowSize = blockColSize * blockRowSize;
	int boardColSize = boardRowSize;
	int i;
	int hints = 30;

	Cell** gameBoard = NULL;
	Cell** solvedBoard = NULL;
	SP_BUFF_SET();
	srand(1);

	parseCommand(testArray, currentCommand);

	gameBoard = (Cell **)malloc(boardRowSize * sizeof(Cell*));
	for(i = 0; i < boardRowSize; i++){
		gameBoard[i] = (Cell *)malloc(boardColSize * sizeof(Cell));
	}

	solvedBoard = (Cell **)malloc(boardRowSize * sizeof(Cell*));
	for(i = 0; i < boardRowSize; i++){
		solvedBoard[i] = (Cell *)malloc(boardColSize * sizeof(Cell));
	}

	createBoards(gameBoard, solvedBoard, blockRowSize, blockColSize, hints);

	/*printBoard(solvedBoard, blockRowSize, blockColSize); */


	return 0;
}
