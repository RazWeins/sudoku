/*
 * MainAux.h
 *
 *  Created on: 12 במאי 2018
 *      Author: beniz
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "Cell.h"

/*
 * Function:  gameLoop
 * --------------------
 *  loop that keeps getting commands from the user
 *
 *	gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *  tempBoard: 2d array holding a sudoku board, just a temp board,values doesn't matter
 */
void gameLoop(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

/*
 * Function:  setAllocatedMem
 * --------------------
 *  creates a 2d array and allocating space for it
 *
 *	returns: pointer to the 2d array
 */
Cell** setAllocatedMem();

#endif /* MAINAUX_H_ */
