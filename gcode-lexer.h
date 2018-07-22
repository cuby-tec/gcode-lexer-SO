/*
 * gcode-lexer.h
 *
 *  Created on: 20.07.2018
 *      Author: walery
 */

#ifndef GCODE_LEXER_H_
#define GCODE_LEXER_H_


#ifdef __cplusplus
   extern "C" {
#endif

#include "sgcode.h"

int setBuffer(char* buf, size_t len);

struct sGcode* getGcode();

void setGcode(struct sGcode* mdst);

char* getErrorComment();


#ifdef __cplusplus
   }
#endif

#endif /* GCODE_LEXER_H_ */
