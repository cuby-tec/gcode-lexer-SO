
#line 1 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
/*
 * A mini G_Code language scanner.
 */

#include "mgParcer.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h>


//#define BUFLEN 512

typedef void (*gfunction)(size_t, char *, size_t );  // Declare typedef

#define INPUT_BUFSIZE 1024

#define FLOG



enum prsCmd{
	eCommand, eComment, eGcommand, eXparam, eOcommand
 	,eStartCommand
	
};


typedef void (*WriteFunc)( char *data, int len );

struct format
{
	char* buf;	//char buf[BUFLEN+1];
	int buflen;
	WriteFunc write;

	int flags;
	int width;
	int prec;
	int cs;
	//--------
	int act;
	char* te;
	char* ts;
	char* p;
	char* pe;
	char* eof;
	int done;	// Исполнение текущего тега.
	int have;
	int curline;
	int space;
	int eofile;
	int lenfile;
	uint state;
	int top;
	int stack[100];
};

//#define curline	fsm->curline

//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;

char buf[INPUT_BUFSIZE];


//	int have = 0, curline = 1;
//	char *ts, *te = 0;
//	int done = 0;


	FILE *fp;
	FILE *flog;
//static void (* parser_out)(size_t number, char * param, size_t len);

static gfunction parser_out;

 void command (size_t curline, char * param, size_t len);
 void gcomment (size_t curline, char * param, size_t len);
 void g_command (size_t curline, char * param, size_t len);
 void x_coordinate(size_t curline, char * param, size_t len);
 void o_command (size_t curline, char * param, size_t len);
void start_command(size_t curline, char * param, size_t len);//eStartCommand
 //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
// void gpunct(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate, &o_command
		, &start_command };


#define gBUFFER_SIZE	100 
 
 char gBuffer[gBUFFER_SIZE];
 
 size_t buffer_index = 0;
 size_t param_index;
 size_t gts;

void append(char ch)
{
	gBuffer[buffer_index++] = ch;
}

void resetBuffer()
{
	gts = 0;
	buffer_index = 0;
	param_index = 0;
	memset(gBuffer,0,gBUFFER_SIZE);
}



void start_command(size_t curline, char * param, size_t len)
{
	//size_t curline, char * param, size_t len
	b_startCommand(curline, param, len);
//	printf("Start command.\n");
	
}

// g Command
 void command (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "Command(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER
		b_command(curline,param,len);
#endif
}

// g comment
 void gcomment (size_t curline, char * param, size_t len){
#ifdef FLOG
		fprintf(flog, "gcomment(%lu): ", curline );
		fwrite( param, 1, len, flog );  
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_gcomment(curline,param,len);
#endif
}

// g GXX.X digit 		=command=	command GXX.X
 void g_command (size_t curline, char * param, size_t len){
#ifdef FLOG	 
		fprintf(flog, "command line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_g_command (curline, param, len);
#endif
}

// g X coordinate
 void x_coordinate(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	 fprintf(flog, "\t parameter line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_x_coordinate (curline, param, len);
#endif
}

 // O command
void o_command (size_t curline, char * param, size_t len){
#ifdef FLOG
	 fprintf(flog, "command line(%lu): ", curline );
		fwrite( param, 1, len, flog );
		fprintf(flog,"\n");
#endif
#ifdef SCANNER		
		b_o_command (curline, param, len);
#endif

}
 
// g *	digit		Checksum 

/*
void gpunct(size_t curline, char * param, size_t len)
{
#ifdef FLOG
	fprintf(flog, "symbol(%lu): %c\n", curline, *param );
#endif
#ifdef SCANNER
	b_punct(curline, param, len);
#endif	
}

*/


// 		punct			Symbols.


#line 327 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"



#line 214 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
static const char _gparcer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 6, 1, 7, 1, 8, 1, 
	9, 1, 10, 2, 5, 1, 2, 6, 
	1, 2, 6, 3, 2, 7, 0, 2, 
	7, 4, 2, 8, 0, 2, 8, 3, 
	2, 9, 0, 2, 9, 6, 2, 10, 
	0, 3, 6, 5, 1
};

static const unsigned char _gparcer_key_offsets[] = {
	0, 0, 1, 4, 5, 10, 14, 16, 
	18, 21, 23, 25, 29, 31, 35, 37, 
	40, 42, 47, 56, 57, 68, 84, 86, 
	100, 102, 115, 118, 120, 124, 137, 142, 
	142, 143, 146, 154, 163, 165, 166, 169, 
	175, 180, 183, 186, 192, 197, 197, 197
};

static const char _gparcer_trans_keys[] = {
	41, 127, 0, 31, 41, 127, 0, 31, 
	32, 126, 41, 127, 0, 31, 48, 57, 
	48, 57, 127, 0, 31, 48, 57, 48, 
	57, 43, 45, 48, 57, 48, 57, 10, 
	46, 48, 57, 48, 57, 10, 48, 57, 
	48, 57, 10, 32, 46, 48, 57, 10, 
	32, 40, 42, 59, 65, 90, 97, 122, 
	41, 10, 32, 40, 42, 59, 9, 13, 
	65, 90, 97, 122, 10, 32, 40, 42, 
	43, 45, 46, 59, 9, 13, 48, 57, 
	65, 90, 97, 122, 48, 57, 10, 32, 
	40, 42, 46, 59, 9, 13, 48, 57, 
	65, 90, 97, 122, 48, 57, 10, 32, 
	40, 42, 59, 9, 13, 48, 57, 65, 
	90, 97, 122, 127, 0, 31, 48, 57, 
	10, 32, 48, 57, 10, 40, 59, 70, 
	71, 77, 79, 0, 82, 83, 84, 85, 
	127, 10, 40, 59, 0, 127, 10, 10, 
	40, 59, 10, 40, 59, 127, 0, 31, 
	32, 126, 10, 40, 41, 59, 127, 0, 
	31, 32, 126, 10, 41, 41, 127, 0, 
	31, 10, 40, 46, 59, 48, 57, 10, 
	40, 59, 48, 57, 10, 40, 59, 10, 
	40, 59, 10, 40, 46, 59, 48, 57, 
	10, 40, 59, 48, 57, 10, 32, 40, 
	42, 59, 9, 13, 65, 90, 97, 122, 
	0
};

static const char _gparcer_single_lengths[] = {
	0, 1, 1, 1, 1, 2, 0, 0, 
	1, 0, 0, 2, 0, 2, 0, 1, 
	0, 3, 5, 1, 5, 8, 0, 6, 
	0, 5, 1, 0, 2, 7, 3, 0, 
	1, 3, 4, 5, 2, 1, 1, 4, 
	3, 3, 3, 4, 3, 0, 0, 5
};

static const char _gparcer_range_lengths[] = {
	0, 0, 1, 0, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 2, 0, 3, 4, 1, 4, 
	1, 4, 1, 1, 1, 3, 1, 0, 
	0, 0, 2, 2, 0, 0, 1, 1, 
	1, 0, 0, 1, 1, 0, 0, 3
};

static const unsigned char _gparcer_index_offsets[] = {
	0, 0, 2, 5, 7, 11, 15, 17, 
	19, 22, 24, 26, 30, 32, 36, 38, 
	41, 43, 48, 56, 58, 67, 80, 82, 
	93, 95, 105, 108, 110, 114, 125, 130, 
	131, 133, 137, 144, 152, 155, 157, 160, 
	166, 171, 175, 179, 185, 190, 191, 192
};

static const char _gparcer_indicies[] = {
	1, 0, 1, 1, 2, 4, 3, 1, 
	1, 5, 2, 8, 7, 7, 6, 9, 
	10, 11, 10, 13, 13, 12, 14, 10, 
	15, 10, 16, 16, 17, 10, 17, 10, 
	18, 19, 17, 10, 20, 10, 18, 20, 
	10, 21, 10, 22, 23, 24, 21, 10, 
	25, 26, 27, 28, 29, 28, 28, 10, 
	31, 30, 33, 32, 27, 28, 29, 32, 
	28, 28, 10, 35, 34, 36, 37, 38, 
	38, 39, 41, 34, 40, 37, 37, 10, 
	40, 10, 35, 34, 36, 37, 39, 41, 
	34, 40, 37, 37, 10, 42, 10, 35, 
	34, 36, 37, 41, 34, 42, 37, 37, 
	10, 31, 31, 43, 44, 10, 22, 23, 
	44, 10, 46, 47, 48, 49, 50, 50, 
	51, 10, 52, 10, 45, 54, 0, 2, 
	10, 53, 10, 54, 10, 55, 56, 57, 
	10, 58, 59, 60, 1, 1, 5, 2, 
	61, 59, 63, 59, 7, 7, 62, 6, 
	64, 1, 0, 1, 0, 1, 1, 2, 
	65, 66, 67, 68, 9, 10, 65, 66, 
	68, 11, 10, 54, 0, 2, 10, 69, 
	70, 71, 10, 54, 0, 72, 2, 14, 
	10, 54, 0, 2, 15, 10, 10, 10, 
	33, 32, 27, 28, 29, 32, 28, 28, 
	10, 0
};

static const char _gparcer_trans_targs[] = {
	1, 32, 2, 3, 33, 34, 5, 36, 
	38, 39, 0, 40, 8, 42, 43, 44, 
	12, 13, 45, 14, 15, 17, 46, 18, 
	27, 46, 18, 19, 21, 26, 19, 20, 
	20, 47, 20, 47, 19, 21, 22, 24, 
	23, 26, 25, 26, 28, 30, 31, 3, 
	4, 6, 41, 8, 9, 30, 31, 31, 
	1, 2, 32, 35, 34, 36, 35, 34, 
	37, 31, 1, 7, 2, 31, 1, 2, 
	10
};

static const char _gparcer_trans_actions[] = {
	0, 9, 0, 0, 9, 0, 0, 9, 
	9, 3, 0, 3, 0, 0, 3, 3, 
	0, 0, 7, 0, 0, 3, 37, 13, 
	5, 7, 0, 19, 19, 19, 3, 22, 
	0, 7, 9, 25, 49, 49, 3, 3, 
	3, 49, 3, 3, 3, 11, 11, 11, 
	11, 11, 31, 11, 11, 0, 0, 15, 
	15, 15, 43, 15, 15, 43, 0, 9, 
	0, 13, 13, 5, 13, 17, 17, 17, 
	5
};

static const char _gparcer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 28, 1, 1, 
	1, 40, 40, 40, 1, 1, 1, 34, 
	34, 1, 46, 1, 1, 0, 0, 0
};

static const int gparcer_start = 29;
static const int gparcer_first_final = 29;
static const int gparcer_error = 0;

static const int gparcer_en_date = 11;
static const int gparcer_en_gname = 16;
static const int gparcer_en_main = 29;


#line 330 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"


struct format fsm;




int format_finish( struct format *fsmp )
{
	if ( fsmp->cs == format_error )
		return -1;
	if ( fsmp->cs >= format_first_final )
		return 1;
	return 0;
}

void format_init( struct format *fsm )
{
	buffer_index = 0;
	fsm->buflen = 0;
	fsm->done = 0;
	//int cs, act, have = 0, curline = 1;
	fsm->have = 0;
	fsm->curline = 1;
	fsm->state = 0;
	
#line 391 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
	{
	( fsm->cs) = gparcer_start;
	( fsm->top) = 0;
	}

#line 356 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
}
static int strnum = 0;
void format_execute( struct format *fsm, char *data, int len, int isEof )
{
//	const char *p = data;
//	const char *pe = data + len;
//	const char *eof = isEof ? pe : 0;
	fsm->curline = ++strnum;
	fsm->buf = data;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	printf("format_execute[892]: len:%d  done:%d line:%d \n",len,fsm->done,fsm->curline);
	if(len == 0)
		return;
	
#line 414 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( ( fsm->p) == ( fsm->pe) )
		goto _test_eof;
	if ( ( fsm->cs) == 0 )
		goto _out;
_resume:
	_keys = _gparcer_trans_keys + _gparcer_key_offsets[( fsm->cs)];
	_trans = _gparcer_index_offsets[( fsm->cs)];

	_klen = _gparcer_single_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*( fsm->p)) < *_mid )
				_upper = _mid - 1;
			else if ( (*( fsm->p)) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _gparcer_range_lengths[( fsm->cs)];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*( fsm->p)) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*( fsm->p)) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _gparcer_indicies[_trans];
	( fsm->cs) = _gparcer_trans_targs[_trans];

	if ( _gparcer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _gparcer_actions + _gparcer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 1:
#line 232 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		append((*( fsm->p)));
//		printf("DGT: %c\n", fc); 
	}
	break;
	case 2:
#line 237 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		append((*( fsm->p)));
//		printf("DEC: .\n"); 
	}
	break;
	case 3:
#line 243 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{ printf("RETURN\n"); {( fsm->cs) = ( fsm->stack)[--( fsm->top)]; goto _again;} }
	break;
	case 4:
#line 245 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
//		append(fc);
//		printf("NAME: %c\n",fc);
		{( fsm->stack)[( fsm->top)++] = ( fsm->cs); ( fsm->cs) = 16; goto _again;} 
	}
	break;
	case 5:
#line 251 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		gts = buffer_index;
		printf("start param: %c\n",(*( fsm->p))); 
	}
	break;
	case 6:
#line 256 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		(*prs[eXparam])(fsm->curline ,&gBuffer[gts],buffer_index - gts);
		fwrite( &gBuffer[gts], 1, buffer_index - gts, stdout );
		printf("\n\tend_param: %c\n",(*( fsm->p))); 
	}
	break;
	case 7:
#line 262 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		resetBuffer();
		append((*( fsm->p)));
		//printf("start_tag: %c\n",fc);
		(*prs[eStartCommand])(fsm->curline ,fsm->p,buffer_index);
	}
	break;
	case 8:
#line 269 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
//		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index-gts);
		fwrite( gBuffer, 1, buffer_index, stdout );
		printf("\ncommand_index: %c\n",(*( fsm->p)));
	}
	break;
	case 9:
#line 275 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		(*prs[eComment])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_comment: %c\n",(*( fsm->p)));
	}
	break;
	case 10:
#line 281 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",(*( fsm->p)));
	}
	break;
#line 562 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
		}
	}

_again:
	if ( ( fsm->cs) == 0 )
		goto _out;
	if ( ++( fsm->p) != ( fsm->pe) )
		goto _resume;
	_test_eof: {}
	if ( ( fsm->p) == ( fsm->eof) )
	{
	const char *__acts = _gparcer_actions + _gparcer_eof_actions[( fsm->cs)];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
#line 225 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		printf("\n action finish_ok.\n");
	}
	break;
	case 7:
#line 262 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		resetBuffer();
		append((*( fsm->p)));
		//printf("start_tag: %c\n",fc);
		(*prs[eStartCommand])(fsm->curline ,fsm->p,buffer_index);
	}
	break;
	case 8:
#line 269 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
//		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index-gts);
		fwrite( gBuffer, 1, buffer_index, stdout );
		printf("\ncommand_index: %c\n",(*( fsm->p)));
	}
	break;
	case 9:
#line 275 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		(*prs[eComment])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_comment: %c\n",(*( fsm->p)));
	}
	break;
	case 10:
#line 281 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",(*( fsm->p)));
	}
	break;
#line 620 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
		}
	}
	}

	_out: {}
	}

#line 372 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	
		if ( format_finish( fsm ) <= 0 ){
//			int as = 1;
			printf("[898] FAIL :finish code:%d  %-10s \n", format_finish( fsm ) ,data);
			assert(format_finish( fsm ) >= 1) ;
		}

	
}

void init(){
	format_init(&fsm);
}

void execute(char *data, int len){
	fsm.done = 0;
	format_execute(&fsm, data, len, true);
}

int finish(){
	return (format_finish(&fsm));
}

#ifdef LOCAL_VERSION
void scanner(){
scannerstart:
	switch (fsm.state)
	{
	case 0:
		fsm.space = INPUT_BUFSIZE - fsm.have;
		fsm.p = fsm.buf + fsm.have;
		
		if ( fsm.space == 0 ) {
			/* We've used up the entire buffer storing an already-parsed token
			 * prefix that must be preserved. */
			fprintf(stderr, "OUT OF BUFFER SPACE\n" );
			exit(1);
		}
	
		fsm.lenfile = fread( fsm.buf+fsm.have, 1, fsm.space, fp );
		
		fsm.eofile = fsm.lenfile != fsm.space;
		
		format_execute( &fsm, fsm.p, fsm.lenfile, fsm.eofile );
		fsm.state = 1;
		 return;
	
	case 1:
		if(fsm.done)
		{
			fsm.done = 0;
			fsm.lenfile = INPUT_BUFSIZE - (fsm.pe - fsm.buf);
			format_execute( &fsm, fsm.pe, fsm.lenfile, fsm.eofile );
			return;
		}
	case 3:
//		printf("[646] done:  %i \n", fsm.done);
		if ( fsm.eofile ){
//			fprintf(stderr, " [650] EOF lenfile:%i  space:%i \n", fsm.lenfile , fsm.space);
			return;
		//	break;
		}	
		
		if ( fsm.ts == 0 ){
			fsm.have = 0;
		}
		else {
			/* There is a prefix to preserve, shift it over. */
			fsm.have = fsm.pe - fsm.ts;
			memmove( fsm.buf, fsm.ts, fsm.have );
			fsm.te = fsm.buf + (fsm.te-fsm.ts);
			fsm.ts = fsm.buf;
		}
	
	}
	
	fsm.state = 0;
	goto scannerstart;

}

#ifndef SCANNER
int _main(int argc, char* argv[])
{

//	int eofile;
//	int len;

	fsm.buf = buf;
	format_init( &fsm );

	char* gfile = "exmple.gcode";
	char* logFile = "gParcer.log";
	
	if(argc == 2){
		gfile = argv[1];
		printf("main[832] param0:%s\n",argv[1]);
	}
	
	if(argc == 3){
		gfile = argv[1];
		logFile = argv[2];
		printf("main[841] gfile:%s\n",gfile);
		printf("main[842] logFile:%s\n",logFile);
	}
	
	
	fp = fopen(gfile,"r");
	   if (fp==NULL) 
	   {
//	   fputs ("File error:"+gfile,stderr); exit (1);
		   fprintf(stderr,"File error: %s",gfile);
	   }else{
		   printf("Open G-file:%s\n",gfile);
	   
	   }
	   
	   
	flog = fopen(logFile,"w");
	   if (flog==NULL) {
//		   fputs ("File error",stderr); exit (1);
		   fprintf(stderr,"Log file error:%s",logFile);
	   }else{
		   printf("Open log file:%s\n",logFile);
	   }


	while(!fsm.eof)
	{	
		scanner();
	}
	
	if ( format_finish( &fsm ) <= 0 )
		printf("[679] FAIL  %li \n", (unsigned long)&fsm);

	printf("main[871]:  %i \n", format_finish( &fsm ));
	
	fclose(fp);
	fclose(flog);
	return 0;
}
#endif
#endif