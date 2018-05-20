/*
 * Parser.c
 *
 *  Created on: 7 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include <string.h>
#include "Game.h"
enum COMMAND{
	set,
	hint,
	validate,
	restart,
	exit1,
	error
};



int parseCommand(char* input, int* command){
	const char delim[7] = " \t\r\n";
	char *token;
	int i;
	token = strtok(input,delim);
	for(i = 0; i < 4; i++){
		command[i] = -1;
	}
	if(token == NULL){
		command[0] = error;
		return -1;
	}
	/* Get the command type */
	if(strcmp(token,"set") == 0){
		command[0] = set;
	}else if(strcmp(token,"hint") == 0){
		command[0] = hint;
	}else if(strcmp(token,"validate") == 0){
		command[0] = validate;
	}else if(strcmp(token,"restart") == 0){
		command[0] = restart;
	}else if(strcmp(token,"exit") == 0){
		command[0] = exit1;
	}else{
		printf("%s", "Error: invalid command\n");
		command[0] = error;
	}
	token = strtok(NULL,delim);
	if(token!= NULL){
		sscanf(token, "%d", &command[2]);
	}
	token = strtok(NULL,delim);
	if((command[0] == 1) && (token == NULL)){
		/* checks if hint is the command and the two params is supplied */
		printf("%s","Error: invalid command\n");
	}
	if(token!= NULL){
		sscanf(token, "%d", &command[1]);
	}
	token = strtok(NULL,delim);
	if((command[0] == 0) && (token == NULL)){
		/* checks if set is the command and the three params is supplied */
		printf("%s","Error: invalid command\n");
	}
	if(token!= NULL){
		sscanf(token, "%d", &command[3]);
	}
	return 0;
}

int validInput(int* command){
	if(command[0] == 5){
		return -1;
	}
	if(command[0] == 0 && (command[1] == -1 || command[2] == -1 || command[3] == -1)){
		return -1;
	}if(command[0] == 1 && (command[1] == -1 || command[2] == -1)){
		return -1;
	}
	return 0;
}


int parseHint(Cell** gameBoard, Cell** solvedBoard, Cell** tempBoard){
	char input[1024];
	char *token;
	const char delim[7] = " \t\r\n";
	int numOfHint;
	printf("%s", "Please enter the number of cells to fill [0-80]:\n");
	if (fgets(input, 1024, stdin) == NULL) {
		/* EOF CASE */
		exitGame(gameBoard, solvedBoard, tempBoard);
	}
	token = strtok(input,delim);
	if(token == NULL){
		return -2;/* blank row, don't exit */
	}
	if(sscanf(token, "%d", &numOfHint) != 1){
		return -1;
	}
	token = strtok(NULL,delim);
	if(token != NULL){
		printf("%s","Error: invalid command\n");
	}
	return numOfHint;
}




