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
	exit,
	error
};



void parseCommand(char* command, int* result){
	const char delim[1] = " ";
	char *token;
	token = strtok(command,delim);

	/* Get the command type */
	if(strcmp(token,"set") == 0){
		result[0] = set;
	}else if(strcmp(token,"hint") == 0){
		result[0] = hint;
	}else if(strcmp(token,"validate") == 0){
		result[0] = validate;
	}else if(strcmp(token,"restart") == 0){
		result[0] = restart;
	}else if(strcmp(token,"exit") == 0){
		result[0] = exit;
	}else{
		result[0] = error;
	}

	if(token!= NULL){
		token = strtok(NULL,delim);
		result[1] = token[0] - 48;
	}
	if(token!= NULL){
		token = strtok(NULL,delim);
		result[2] = token[0] - 48;
	}
	if(token!= NULL){
		token = strtok(NULL,delim);
		result[3] = token[0] - 48;
	}

}





