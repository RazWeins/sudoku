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
void boardInitWithNums(Cell** table, char str[81]){
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
/*
char* boardToString(Cell** board){
	int i, j, k = 0;
	int boardRow = BLOCK_ROW_SIZE * BLOCK_COL_SIZE;
	int boardCol = boardRow;
	char str[83];
	for(i = 0; i < boardRow; i++){
		for(j = 0; j < boardCol; j++){
			str[k] = board[i][j].currentNum;
			k++;
		}
	}
	str[81] = "\0";
	return str;
}
*/

void testSolver(){
	Cell** gameBoard = NULL;

	gameBoard = setAllocatedMem();

	/* full board */
	boardInitWithNums(gameBoard,"974236158638591742125487936316754289742918563589362417867125394253649871491873625");
	if(sudokuSolver(gameBoard) == -1){
		printf("%s","OK");
	}else{
		printf("%s","ERROR:sudoku solver;full");
	}

	/* last cell */
	boardInitWithNums(gameBoard,"256489173374615982981723456593274861712806549468591327635147298127958634849362715");
	if(sudokuSolver(gameBoard) == -1 && gameBoard[4][4].currentNum == 3){
		printf("%s","OK");
	}else{
		printf("%s","ERROR:sudoku solver ; single num");
	}

	/* Naked Singles */
	boardInitWithNums(gameBoard,"305420810487901506029056374850793041613208957074065280241309065508670192096512408");
	if(sudokuSolver(gameBoard) == -1 && gameBoard[4][4].currentNum == 3){
		printf("%s","OK");
	}else{
		printf("%s","ERROR:sudoku solver ; single num");
	}
}
