/*
 * Parser.h
 *
 *  Created on: 7 ���� 2018
 *      Author: beniz
 */

#ifndef PARSER_H_
#define PARSER_H_

enum COMMAND{
	set,
	hint,
	validate,
	restart,
	exit1,
	error
};

void parseCommand(char* command, int* result);


#endif /* PARSER_H_ */
