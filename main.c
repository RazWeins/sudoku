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
int main() {
	/*
	Cell** gameBoard = NULL;
	Cell** solvedBoard = NULL;
	Cell** tempBoard = NULL;

	SP_BUFF_SET();
	srand(1);

	tempBoard = setAllocatedMem();
	gameBoard = setAllocatedMem();
	solvedBoard = setAllocatedMem();

	gameLoop(gameBoard, solvedBoard, tempBoard);*/
	testSolver();

	return 0;
}
