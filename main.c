/*
 * main.c
 *
 *  Created on: 7 May 2018
 *      Author: Raz
 */
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"
#include "MainAux.h"
#include "Cell.h"
#include "def.h"
int main() {

	/* Declarations */
	int boardRowSize = BLOCK_COL_SIZE * BLOCK_ROW_SIZE;
	int boardColSize = boardRowSize;
	int i;

	Cell** gameBoard = NULL;
	Cell** solvedBoard = NULL;
	Cell** tempBoard = NULL;

	SP_BUFF_SET();
	srand(1);

	tempBoard = (Cell **) malloc(boardRowSize * sizeof(Cell*));
	gameBoard = (Cell **) malloc(boardRowSize * sizeof(Cell*));
	solvedBoard = (Cell **) malloc(boardRowSize * sizeof(Cell*));
	for (i = 0; i < boardRowSize; i++) {
		solvedBoard[i] = (Cell *) malloc(boardColSize * sizeof(Cell));
		gameBoard[i] = (Cell *) malloc(boardColSize * sizeof(Cell));
		tempBoard[i] = (Cell *) malloc(boardColSize * sizeof(Cell));
	}

	gameLoop(gameBoard, solvedBoard, tempBoard);

	return 0;
}
