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

/*char* getStatus();
int isValid();
char hint(int X, int Y);
int setCell(int X, int Y, int Z);
*/

#endif /* GAME_H_ */
