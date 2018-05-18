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


void boardInit(Cell** table, int boardRowSize, int boardColSize);

void createBoards(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize, int amountOfHints);

int setCell(Cell** table, int cellRow, int cellCol, int cellValue, int blockRowSize, int blockColSize);

void hintCell(Cell** table, int cellRow, int cellCol);

void validateBoard(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard,int blockRowSize, int blockColSize);

void exitGame(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard);

#endif /* GAME_H_ */
