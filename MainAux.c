/*
 * MainAux.c
 *
 *  Created on: 12 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Game.h"
#include  "Solver.h" /* just for "printGame" function */

/* TODO check EOF */



/* get the input from the user until reached EOF */
int getInput(char input[], int command[]){
	if(fgets(input, 1024, stdin) == NULL){
		/* EOF CASE */
		return -1;
	}
	parseCommand(input, command);
	while(validInput(command) == -1){
		if(fgets(input, 1024, stdin) == NULL){
			/* EOF CASE */
			return -1;
		}
		parseCommand(input, command);
	}
	return 0;
}

/* gets the number of hints from the user and initialize the boards accordingly
 * if EOF was entering the function returns -1, else 0*/
int initGame(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize){
	char input[1024];
	int numOfHint;
	printf("%s", "Please enter the number of cells to fill [0-80]:\n");
	if(fgets(input, 1024, stdin) == NULL){
		/* EOF CASE */
		return -1;
	}
	sscanf(input, "%d", &numOfHint);
	while(numOfHint > 80 || numOfHint < 0){
		printf("%s", "Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		printf("%s", "Please enter the number of cells to fill [0-80]:\n");
		fgets(input, 1024, stdin);
		sscanf(input, "%d", &numOfHint);
	}
	createBoards(gameBoard, solvedBoard, blockRowSize, blockColSize, numOfHint);
	return 0;
}

int gameLoop(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize){
	char input[1024];
	int command[4];
	int exitFlag = 0;
	if(initGame(gameBoard, solvedBoard, blockRowSize, blockColSize) == -1){
		/* EOF CASE */
		return -1;
	}
	while(exitFlag == 0){
		exitFlag = getInput(input, command);

	}



	return 0;
}




