
#ifndef GHELPER_H
#define GHELPER_H




//#ifdef __cplusplus
//   extern "C" {
//#endif
//--------------------defs
#define SCANNER

#include "sgcode.h"
//#include "ghelper.h"

//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

//---------------- var

extern struct sGcode sgcode;

extern struct sGcode* dst;

//--------------- function

//#ifdef SCANNER
extern void clear_sgcode();

extern struct sGcode* getSgcode();

extern void b_command (size_t curline, char * param, size_t len);
extern void b_gcomment (size_t curline, char * param, size_t len);
extern void b_g_command (size_t curline, char * param, size_t len);
extern void b_x_coordinate(size_t curline, char * param, size_t len);
extern void b_o_command (size_t curline, char * param, size_t len); // O command
extern void b_startCommand(size_t curline, char * param, size_t len);

extern void h_add_lineNumber(char* param, size_t len);
extern void h_comment(char* data, size_t len);

extern void b_endtag();

//extern void b_punct(size_t curline, char* param, size_t len);
//#endif
//#ifdef __cplusplus
//   }
//#endif


#endif // GHELPER_H
