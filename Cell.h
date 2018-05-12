/*
 * Cell.h
 *
 *  Created on: 11 במאי 2018
 *      Author: beniz
 */

#ifndef CELL_H_
#define CELL_H_

struct _Cell
{
	int currentNum;
	int fixed;
	int limit;
	int isInput;
	int validNums[9];
	int prevNums[9];
};

typedef struct _Cell Cell;

#endif /* CELL_H_ */
