/*
 * gcode-lexer.c
 *
 *  Created on: 20.07.2018
 *      Author: walery
 */

#include "gcode-lexer.h"

#include "mgParcer.h"

int setBuffer(char* buf, size_t len)
{
	int result;

	init();

	execute(buf,len);

	return result;
}

struct sGcode* getGcode()
{
	struct sGcode* result;



	return result;
}

char* getErrorComment()
{
	char* result;



	return result;
}
