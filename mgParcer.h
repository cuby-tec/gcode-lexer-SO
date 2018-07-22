/**
 *  File: gParcer.h
 * Company: CUBY,Ltd
*/

#ifndef MGPARCER
#define MGPARCER

//#ifdef __cplusplus
//   extern "C" {
//#endif

//#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ghelper.h"

//#define FLOG_no
//#define SCANNER


// ------------- vars
//extern FILE *flog;


#ifdef SCANNER
extern void b_command (size_t curline, char * param, size_t len);
extern void b_gcomment (size_t curline, char * param, size_t len);
extern void b_g_command (size_t curline, char * param, size_t len);
extern void b_o_command (size_t curline, char * param, size_t len); // O command
extern void b_x_coordinate(size_t curline, char * param, size_t len);
extern void b_startCommand(size_t curline, char * param, size_t len);

extern void h_add_lineNumber(char* param, size_t len);
extern void h_comment(char* data, size_t len);

extern void b_endtag();

//extern void b_punct(curline, param, len);
#endif


//----------- function

//extern void scanner();

extern int execute(char *data, int len);

extern void init();

extern int finish();

//#ifdef __cplusplus
//   }
//#endif

#endif

