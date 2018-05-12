/*
 * MainAux.c
 *
 *  Created on: 12 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include "Parser.h"
#include "Game.h"

/* TODO check EOF and if scanf is ok to get number of hints*/

void initGame(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize){
	int numOfHint;
	printf("%s", "Please enter the number of cells to fill [0-80]:\n");
	scanf("%d", &numOfHint);
	while(numOfHint > 80 || numOfHint < 0){
		printf("%s", "Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		printf("%s", "Please enter the number of cells to fill [0-80]:\n");
		scanf("%d", &numOfHint);
	}
	createBoards(gameBoard, solvedBoard, blockRowSize, blockColSize, numOfHint);
}

