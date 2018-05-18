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
 *
 * input:
 * table-intialized 2d array */
void sudokuGenerator(Cell** table);

/* solves the puzzle deterministically
 *
 * input:
 * table-intialized 2d array
 *
 * output:
 * 0 - not solvable
 * -1 - solvable*/
int sudokuSolver(Cell** table);

/* checks if assigning numToCheck at cellCol,cellRow is a valid assignment
 *
 * input:
 * table-intialized 2d array
 * numToCheck - number to assign
 * cellRow - row of cell to be assigned to
 * cellCol - column of cell to be assigned to
 *
 * output:
 * 0 - valid assignment
 * -1 - invalid assignment*/
int validAssignment(Cell** table, int numToCheck, int cellRow, int cellCol);

#endif /* SOLVER_H_ */
