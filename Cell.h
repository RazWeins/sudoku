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
	int currentNum; /* the cell current appearing number */
	int fixed;/* flag if cell is a fixed number */
	int limit;/* current last index of validnums */
	int isInput;/* flag if the value in this cell is an input by the user */
	int validNums[9]; /* array holding current valid numbers */
	int prevNums[9]; /* array holding numbers which were tried previously */
};

typedef struct _Cell Cell;

#endif /* CELL_H_ */
