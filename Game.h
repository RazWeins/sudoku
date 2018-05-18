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

void printBoard(Cell** table);

void boardInit(Cell** table);

int setCell(Cell** table, int cellRow, int cellCol, int cellValue);

void hintCell(Cell** table, int cellRow, int cellCol);

void validateBoard(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

void exitGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

void puzzleGeneration(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard, int amountOfHints);

#endif /* GAME_H_ */
