/*
 * Parser.c
 *
 *  Created on: 7 במאי 2018
 *      Author: beniz
 */
#include <stdio.h>
#include <string.h>

enum COMMAND{
	set,
	hint,
	validate,
	restart,
	exit1,
	error
};



void parseCommand(char* input, int* command){
	/***************************************************************
	 * get array of chars which represent the command from the user*
	 * and change the result array accordingly. the first variable *
	 * in the result array is the command type and the rest are the*
	 * parameters for the command                                  *
	 ***************************************************************/
	const char delim[1] = " ";
	char *token;
	token = strtok(input,delim);
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
	if(token!= NULL){
		token = strtok(NULL,delim);
		sscanf(token, "%d", &command[2]);
	}
	if(token!= NULL){
		token = strtok(NULL,delim);
		sscanf(token, "%d", &command[1]);
	}
	if(token!= NULL){
		token = strtok(NULL,delim);
		sscanf(token, "%d", &command[3]);
	}
}



/* check if the input is in the correct range or if error accrued
 * return 0 if yes or -1 if not */
int validInput(int* command){
	if(command[0] == 5){
		return -1;
	}
	if(command[0] == 0){
		/* check that the arguments for the SET command are in the correct range */
		if((command[1] < 1) || (command[1] > 9)){
			return -1;
		}
		if((command[2] < 1) || (command[2] > 9)){
			return -1;
		}
		if((command[3] < 0) || (command[3] > 9)){
			return -1;
		}
	}else if(command[0] == 1){
		/* check that the arguments for the SET command are in the correct range */
		if((command[1] < 1) || (command[1] > 9)){
			return -1;
		}
		if((command[2] < 1) || (command[2] > 9)){
			return -1;
		}
	}
	return 0;
}






