/*
 * Game.h
 *
 *  Created on: 7 May 2018
 *      Author: Raz
 */

#ifndef GAME_H_
#define GAME_H_
#include "Solver.h"
#include "Cell.h"

/*
 * Function:  printBoard
 * --------------------
 *  prints a sudoku board
 *
 *  table: 2d array holding a sudoku board
 *
 */
void printBoard(Cell** table);

/*
 * Function:  boardInit
 * --------------------
 *  intializes a 2d array with zeros and each cell's fields with it's default values
 *
 *  table: 2d array holding a sudoku board
 *
 */
void boardInit(Cell** table);

/*
 * Function:  setCell
 * --------------------
 *  setting a cell at (cellCol,cellRow) with cellValue, only if it's a valid value.
 *
 *  table: 2d array holding a sudoku board
 *  cellRow: the cell's row
 *  cellCol: the cell's column
 *  cellValue:the value to set the cell to
 *
 *  returns: 1 if board is solved else returns 0.
 *
 */
int setCell(Cell** table, int cellRow, int cellCol, int cellValue);

/*
 * Function:  hintCell
 * --------------------
 *  returns a correct input to cell at (cellCol,cellRow)
 *
 *  table: 2d array holding a sudoku board
 *  cellRow: the cell's row
 *  cellCol: the cell's column
 */
void hintCell(Cell** table, int cellRow, int cellCol);

/*
 * Function:  validateBoard
 * --------------------
 *  returns a correct input to cell at (cellCol,cellRow)
 *
 *  gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *  tempBoard: 2d array holding a sudoku board, just a temp board,values doesn't matter
 */
void validateBoard(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

/*
 * Function:  exitGame
 * --------------------
 *  exits game by freeing allocated memory, printing exit message and exits program
 *
 *  gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *  tempBoard: 2d array holding a sudoku board, just a temp board,values doesn't matter
 */
void exitGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

/*
 * Function:  puzzleGeneration
 * --------------------
 * initializes gameboard,solvedboard and tempboard with boardInit, generates a suduko puzzle
 * in solvedBoard and sets hints in amount of amountOfHints then calls createGameBoard
 *
 *  gameBoard: 2d array holding a sudoku board, it holds the board the user is playing on
 *  solvedBoard: 2d array holding a sudoku board, it holds a solved board
 *  tempBoard: 2d array holding a sudoku board, just a temp board,values doesn't matter
 *  amountOfHints: amount of cells to be fixed with a valid value
 */
void puzzleGeneration(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard, int amountOfHints);

#endif /* GAME_H_ */
