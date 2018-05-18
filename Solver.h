/*
 * Solver.h
 *
 *  Created on: 11 ���� 2018
 *      Author: beniz
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Cell.h"

/* generates a new sudoku puzzle using the random backtracking algorithm.
 * input:table: intialized 2d array */
void sudokuGenerator(Cell** table, int blockRowSize, int blockColSize);

int dtrBacktrackWrap(Cell** table, int blockRowSize, int blockColSize);

int validAssignment(Cell** table, int numToCheck, int cellRow, int cellCol, int blockRowSize, int blockColSize);


#endif /* SOLVER_H_ */
