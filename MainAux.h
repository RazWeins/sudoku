/*
 * MainAux.h
 *
 *  Created on: 12 במאי 2018
 *      Author: beniz
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_


/* the function initialize the game, receive commands from user and call the right function
 * to handle it. if the command is restart the function return 3, if the command is exit the
 * function return 4 */
int gameLoop(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize);

void initGame(Cell** gameBoard, Cell** solvedBoard, int blockRowSize, int blockColSize);

#endif /* MAINAUX_H_ */
