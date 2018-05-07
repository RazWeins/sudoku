/*
 * main.c
 *
 *  Created on: 7 May 2018
 *      Author: Raz
 */
#include <stdio.h>
#include "SPBufferset.h"
#include "Parser.h"


int main(){
	/* Declarations */
	char testArray[1024] = "set 2 3 4";
	int currentCommand[4] = {0,0,0,0};
	SP_BUFF_SET();

	parseCommand(testArray, currentCommand);


	return 0;
}

