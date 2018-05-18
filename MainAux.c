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

/* TODO check EOF */

/* get the input from the user until reached EOF */
int getInput(char input[], int command[]) {
	if (fgets(input, 1024, stdin) == NULL) {
		/* EOF CASE */
		return -1;
	}
	parseCommand(input, command);
	while (validInput(command) == -1) {
		if (fgets(input, 1024, stdin) == NULL) {
			/* EOF CASE */
			return -1;
		}
		parseCommand(input, command);
	}
	return 0;
}

/* gets the number of hints from the user and initialize the boards accordingly
 * if EOF was entering the function returns -1, else 0*/
int initGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard,
		int blockRowSize, int blockColSize) {
	char input[1024];
	int numOfHint;
	printf("%s", "Please enter the number of cells to fill [0-80]:\n");
	if (fgets(input, 1024, stdin) == NULL) {
		/* EOF CASE */
		return -1;
	}
	sscanf(input, "%d", &numOfHint);
	while (numOfHint > 80 || numOfHint < 0) {
		printf("%s",
				"Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		printf("%s", "Please enter the number of cells to fill [0-80]:\n");
		fgets(input, 1024, stdin);
		sscanf(input, "%d", &numOfHint);
	}
	puzzleGeneration(gameBoard, solvedBoard, tempBoard, blockRowSize,
			blockColSize, numOfHint);
	return 0;
}

void commmandRouter(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard,
		int blockRowSize, int blockColSize, int command[]) {
	switch (command[0]) {
	case 0:/* Set X Y Z */
		setCell(gameBoard, command[1], command[2], command[3], blockRowSize,
				blockColSize);
		break;
	case 1: /* Hint X Y */
		hintCell(solvedBoard, command[1], command[2]);
		break;
	case 2: /* validate */
		validateBoard(gameBoard, solvedBoard, tempBoard, blockRowSize,
				blockColSize);
		break;
	case 3:/* restart */
		initGame(gameBoard, solvedBoard, tempBoard, blockRowSize, blockColSize);
		break;
	case 4:
		exitGame(gameBoard, solvedBoard, tempBoard);
		break;
	}
}

void gameLoop(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard, int blockRowSize, int blockColSize) {
	char input[1024];
	int command[4];
	int exitFlag = 0;
	if (initGame(gameBoard, solvedBoard, tempBoard, blockRowSize, blockColSize) == -1) {
		/* EOF CASE */
		exitGame(gameBoard, solvedBoard, tempBoard);
	}
	printBoard(gameBoard, blockRowSize, blockColSize);
	while (exitFlag == 0) {
		exitFlag = getInput(input, command);
		commmandRouter(gameBoard, solvedBoard, tempBoard, blockRowSize,
				blockColSize, command);
		printBoard(gameBoard, blockRowSize, blockColSize);
	}
}

