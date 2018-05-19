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
#include "solverUnitTest.h"
int main(int argc, char *argv[]) {
	int seed;
	Cell** gameBoard = NULL;
	Cell** solvedBoard = NULL;
	Cell** tempBoard = NULL;

	SP_BUFF_SET();
	if(argc > 1){
		sscanf(argv[1], "%d", &seed);
		printf("%s","the seed is: ");
		printf("%d", seed);
		printf("%s","\n");
	}

	tempBoard = setAllocatedMem();
	gameBoard = setAllocatedMem();
	solvedBoard = setAllocatedMem();

	gameLoop(gameBoard, solvedBoard, tempBoard);


	return 0;
}
