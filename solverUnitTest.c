/*
 * solverUnitTest.c
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

/* initializes board with zeros */
void boardInitWithNums(Cell** table, char str[83]){
	int i, j, k, m = 0;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int boardCol = boardRow;
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){

			for (k = 0; k < 9; k++) {/* initializes prevNums as not used nums*/
				table[i][j].prevNums[k] = 0;
			}

			table[i][j].currentNum = str[m] - 48;
			table[i][j].fixed = 0;
			if(table[i][j].currentNum == 0){
				table[i][j].isInput = 0;
			}else{
				table[i][j].isInput = 1;
			}
			table[i][j].limit = 9;
			m++;

		}
	}
}

void boardToString(Cell** board, char *str){
	int i, j, k = 0;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int boardCol = boardRow;
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			str[k] = board[i][j].currentNum + 48;
			k++;
		}
	}
	str[81] = '\0';
}


void testSolver(){
	Cell** gameBoard = NULL;
	int out;
	char str[83];

	gameBoard = setAllocatedMem();

	/* full board */
	boardInitWithNums(gameBoard,"974236158638591742125487936316754289742918563589362417867125394253649871491873625");
	if(sudokuSolver(gameBoard) == -1){
		printf("%s","OK\n");
	}else{
		printf("%s","ERROR:sudoku solver;full\n");
	}

	/* last cell */
	boardInitWithNums(gameBoard,"256489173374615982981723456593274861712806549468591327635147298127958634849362715");
	if(sudokuSolver(gameBoard) == -1 && gameBoard[4][4].currentNum == 3){
		printf("%s","OK\n");
	}else{
		printf("%s","ERROR:sudoku solver ; single num\n");
	}

	/* Naked Singles */
	boardInitWithNums(gameBoard,"305420810487901506029056374850793041613208957074065280241309065508670192096512408");
	out = sudokuSolver(gameBoard);
	boardToString(gameBoard, str);

	if((out == -1) && (strcmp(str,"365427819487931526129856374852793641613248957974165283241389765538674192796512438") == 0)){
		printf("%s","OK\n");
	}else{
		printf("%s", str);
		printf("%s", "\n");
		printf("%s","backtrack outputs: ");
		printf("%d", out);
		printf("%s", "\n");
		printf("%s","ERROR:sudoku solver ; Naked Singles\n");
	}
}
