/*
 * Parser.h
 *
 *  Created on: 7 במאי 2018
 *      Author: beniz
 */

#ifndef PARSER_H_
#define PARSER_H_

/* enum for different types of commands */
enum COMMAND{
	set,
	hint,
	validate,
	restart,
	exit1,
	error
};

/*
 * Function:  parseCommand
 * --------------------
 * get array of chars which represent the command from the user*
 * and change the result array accordingly. the first variable *
 * in the result array is the command type and the rest are the*
 * parameters for the command
 *
 *  input: string of the input by the user
 *  command: array holding types of commands
 *
 *  returns: -1 if input is empty or 0 if valid
 */
int parseCommand(char* input, int* command);

/*
 * Function:  validInput
 * --------------------
 * check if the input is in the correct range or if error accrued
 * return 0 if yes or -1 if not
 *
 *  command: array holding types of commands
 */
int validInput(int* command);

/*
 * Function:  parseHint
 * --------------------
 * if the read was successful the function returned
 * the number of hints, else return -1
 *
 *  returns: number of hints if read was not successful return -1
 */
int parseHint();


#endif /* PARSER_H_ */
