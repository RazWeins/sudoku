/*
 * Solver.h
 *
 *  Created on: 11 במאי 2018
 *      Author: beniz
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Cell.h"

int rndBacktrackWrap(Cell** table, int blockRowSize, int blockColSize);

int dtrBacktrackWrap(Cell** table, int blockRowSize, int blockColSize);

void printBoard(Cell** table, int blockRowSize, int blockColSize);

#endif /* SOLVER_H_ */
