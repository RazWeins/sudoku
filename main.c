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

int main(){

	/* Declarations */
	char testArray[1024] = "set 2 3 4";
	int currentCommand[4] = {0,0,0,0};
	int blockRowSize = 3;
	int blockColSize = 3;
	int boardRowSize = blockColSize * blockRowSize;
	int boardColSize = blockColSize * blockRowSize;
	int i;
	Cell** table  = (Cell **)malloc(boardRowSize * sizeof(Cell*));

	for(i = 0; i < boardRowSize; i++){
		table[i] = (Cell *)malloc(boardColSize * sizeof(Cell));
	}

	SP_BUFF_SET();
	srand(20);

	parseCommand(testArray, currentCommand);

	boardInit(table, boardRowSize, boardColSize);

	printf("%s", "\n");

	rndBacktrackWrap(table, blockRowSize, blockColSize);

	printBoard(table, blockRowSize, blockColSize);

	return 0;
}
