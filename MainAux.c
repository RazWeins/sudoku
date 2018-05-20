/*
 * MainAux.c
 *
 *  Created on: 12 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "Game.h"
#include "def.h"

Cell** setAllocatedMem(){
	int boardRowSize = BLOCK_COL_SIZE * BLOCK_ROW_SIZE;
	int boardColSize = boardRowSize;
	int i;

	Cell** temp = (Cell **) malloc(boardRowSize * sizeof(Cell*));
	if(temp == NULL){
		printf("%s","Error: setAllocatedMem has failed\n");
		return NULL;
	}
	for (i = 0; i < boardRowSize; i++) {
		temp [i] = (Cell *) malloc(boardColSize * sizeof(Cell));
		if(temp[i] == NULL){
				printf("%s","Error: setAllocatedMem has failed\n");
				return NULL;
			}
	}
	return temp;
}

/*
 * Function:  getInput
 * --------------------
 *  gets input from user and uses parseCommand to parse it
 *  if command is not a valid command it keeps looping until
 *  it gets a valid command
 *
 *  returns: -1 if there's EOF and returns 0 if not
 *
 */
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

/*
 *  Function:  initGame
 * --------------------
 *  gets the number of hints from the user and initialize
 *  the boards accordingly with puzzleGeneration
 *  then prints the created gameBoard using printBoard
 *
 *  returns: -1 if there's EOF else returns 0
 *
 */
int initGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard) {
	int numOfHint;
	numOfHint = parseHint();
	if(numOfHint == -1){
		exitGame(gameBoard, solvedBoard, tempBoard);
	}
	while (numOfHint > 80 || numOfHint < 0) {
		printf("%s",
				"Error: Invalid number of cells to fill (should be between 0 and 80)\n");
		numOfHint = parseHint();
		if(numOfHint == -1){
			exitGame(gameBoard, solvedBoard, tempBoard);
		}
	}
	puzzleGeneration(gameBoard, solvedBoard, tempBoard, numOfHint);
	printBoard(gameBoard);
	return 0;
}

/*
 *  Function:  commmandRouter
 * --------------------
 *  checking type of command by value in first cell of command
 *  then calls the right command
 *
 *  gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *  tempBoard: 2d array holding a sudoku board, just a temp board,values doesn't matter
 *  command: array holding:
 *  [0]:type of command, [1]: value of cell's column, [2]: value of cell's row, [3]: value to set to.
 *
 */
void commmandRouter(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard, int command[]) {
	switch (command[0]) {
	case 0:/* Set X Y Z */
		setCell(gameBoard, command[1], command[2], command[3]);
		break;
	case 1: /* Hint X Y */
		hintCell(solvedBoard, command[1], command[2]);
		break;
	case 2: /* validate */
		validateBoard(gameBoard, solvedBoard, tempBoard);
		break;
	case 3:/* restart */
		if(initGame(gameBoard, solvedBoard, tempBoard) == -1){
			/* EOF CASE */
			exitGame(gameBoard, solvedBoard, tempBoard);
		}
		break;
	case 4:
		exitGame(gameBoard, solvedBoard, tempBoard);
		break;
	}
}

void gameLoop(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard) {
	char input[1024];
	int command[4];
	int exitFlag = 0;
	if (initGame(gameBoard, solvedBoard, tempBoard) == -1) {
		/* EOF CASE */
		exitGame(gameBoard, solvedBoard, tempBoard);
	}
	while (exitFlag == 0) {
		exitFlag = getInput(input, command);
		commmandRouter(gameBoard, solvedBoard, tempBoard, command);
	}
}

