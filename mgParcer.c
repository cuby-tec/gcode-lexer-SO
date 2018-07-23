
#line 1 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
/*
 * A mini G_Code language scanner.
 */

#include "mgParcer.h"
//#include "ghelper.h"


//#define FLOG

struct m_format
{
	char* buf;	//char buf[BUFLEN+1];
	int buflen;
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
	int state;//uint
	int top;
	int stack[100];
};


//------------------- vars

static const int format_start = 11;
static const int format_first_final = 11;
static const int format_error = 0;


#define gBUFFER_SIZE	100 
 
 char gBuffer[gBUFFER_SIZE];
 
 size_t buffer_index = 0;
 size_t param_index;
 size_t gts;
 char* start_tag;
 int has_return;
 
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



#line 199 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"



#line 77 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
static const char _gparcer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 6, 1, 7, 1, 8, 1, 
	9, 1, 10, 1, 11, 1, 12, 1, 
	13, 2, 1, 3, 2, 1, 5, 2, 
	1, 6, 2, 1, 13, 2, 5, 1, 
	2, 6, 3, 2, 6, 13, 2, 7, 
	4, 2, 8, 3, 2, 8, 13, 2, 
	9, 0, 2, 10, 0, 2, 11, 7, 
	2, 14, 3, 2, 14, 13, 3, 1, 
	6, 3, 3, 1, 6, 5, 3, 1, 
	6, 13, 3, 1, 14, 3, 3, 1, 
	14, 13, 3, 6, 5, 1, 3, 6, 
	14, 3, 3, 6, 14, 13, 3, 8, 
	5, 1, 3, 11, 7, 4, 4, 1, 
	6, 14, 3, 4, 1, 6, 14, 13
	
};

static const short _gparcer_key_offsets[] = {
	0, 0, 1, 2, 4, 6, 18, 27, 
	30, 32, 43, 47, 49, 53, 55, 58, 
	60, 72, 81, 82, 91, 104, 118, 128, 
	133, 146, 159, 163, 176, 190, 204, 206, 
	217, 237, 253, 253, 255, 256, 260, 265, 
	266, 268, 270, 282, 282, 291, 301, 302
};

static const char _gparcer_trans_keys[] = {
	41, 41, 32, 126, 48, 57, 32, 40, 
	46, 59, 77, 79, 48, 57, 70, 71, 
	83, 84, 32, 40, 59, 77, 79, 70, 
	71, 83, 84, 127, 0, 31, 48, 57, 
	32, 40, 59, 77, 79, 48, 57, 70, 
	71, 83, 84, 43, 45, 48, 57, 48, 
	57, 10, 46, 48, 57, 48, 57, 10, 
	48, 57, 48, 57, 10, 32, 40, 42, 
	46, 59, 9, 13, 48, 57, 65, 90, 
	10, 32, 40, 42, 59, 9, 13, 65, 
	90, 41, 10, 32, 40, 42, 59, 9, 
	13, 65, 90, 10, 32, 40, 42, 59, 
	9, 13, 33, 64, 65, 90, 91, 126, 
	10, 32, 40, 41, 42, 59, 9, 13, 
	33, 64, 65, 90, 91, 126, 10, 32, 
	40, 41, 42, 59, 9, 13, 65, 90, 
	10, 41, 59, 32, 126, 10, 32, 40, 
	42, 59, 9, 13, 33, 64, 65, 90, 
	91, 126, 10, 32, 40, 42, 59, 9, 
	13, 33, 64, 65, 90, 91, 126, 10, 
	59, 32, 126, 10, 32, 40, 42, 59, 
	9, 13, 33, 64, 65, 90, 91, 126, 
	10, 32, 40, 41, 42, 59, 9, 13, 
	33, 64, 65, 90, 91, 126, 10, 32, 
	40, 41, 42, 59, 9, 13, 33, 64, 
	65, 90, 91, 126, 48, 57, 10, 32, 
	40, 42, 59, 9, 13, 48, 57, 65, 
	90, 32, 40, 59, 77, 78, 79, 0, 
	8, 9, 13, 14, 69, 70, 71, 72, 
	82, 83, 84, 85, 127, 10, 40, 59, 
	77, 78, 79, 0, 69, 70, 71, 72, 
	82, 83, 84, 85, 127, 10, 40, 10, 
	10, 40, 32, 126, 10, 40, 41, 32, 
	126, 41, 10, 40, 10, 40, 32, 40, 
	59, 77, 78, 79, 9, 13, 70, 71, 
	83, 84, 10, 32, 40, 42, 59, 9, 
	13, 65, 90, 10, 32, 40, 41, 42, 
	59, 9, 13, 65, 90, 41, 0
};

static const char _gparcer_single_lengths[] = {
	0, 1, 1, 0, 0, 6, 5, 1, 
	0, 5, 2, 0, 2, 0, 1, 0, 
	6, 5, 1, 5, 5, 6, 6, 3, 
	5, 5, 2, 5, 6, 6, 0, 5, 
	6, 6, 0, 2, 1, 2, 3, 1, 
	2, 2, 6, 0, 5, 6, 1, 0
};

static const char _gparcer_range_lengths[] = {
	0, 0, 0, 1, 1, 3, 2, 1, 
	1, 3, 1, 1, 1, 1, 1, 1, 
	3, 2, 0, 2, 4, 4, 2, 1, 
	4, 4, 1, 4, 4, 4, 1, 3, 
	7, 5, 0, 0, 0, 1, 1, 0, 
	0, 0, 3, 0, 2, 2, 0, 0
};

static const short _gparcer_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 18, 26, 
	29, 31, 40, 44, 46, 50, 52, 55, 
	57, 67, 75, 77, 85, 95, 106, 115, 
	120, 130, 140, 144, 154, 165, 176, 178, 
	187, 201, 213, 214, 217, 219, 223, 228, 
	230, 233, 236, 246, 247, 255, 264, 266
};

static const char _gparcer_indicies[] = {
	1, 0, 3, 2, 4, 5, 6, 5, 
	7, 8, 9, 10, 11, 12, 6, 11, 
	11, 5, 13, 14, 15, 16, 17, 16, 
	16, 5, 19, 19, 18, 20, 5, 7, 
	8, 10, 11, 12, 20, 11, 11, 5, 
	21, 21, 22, 5, 22, 5, 23, 24, 
	22, 5, 25, 5, 23, 25, 5, 26, 
	5, 28, 27, 29, 30, 31, 32, 27, 
	26, 30, 5, 34, 33, 35, 36, 37, 
	33, 36, 5, 39, 38, 41, 40, 42, 
	43, 44, 40, 43, 5, 41, 40, 46, 
	47, 48, 40, 45, 47, 45, 5, 50, 
	49, 46, 45, 46, 52, 49, 51, 46, 
	51, 38, 54, 53, 55, 39, 56, 57, 
	53, 56, 38, 58, 60, 61, 59, 38, 
	62, 63, 65, 66, 67, 40, 64, 66, 
	64, 5, 68, 69, 70, 71, 72, 33, 
	64, 71, 64, 5, 73, 72, 64, 5, 
	62, 63, 75, 76, 77, 40, 74, 76, 
	74, 5, 78, 79, 75, 74, 75, 81, 
	49, 80, 75, 80, 38, 82, 83, 84, 
	60, 85, 61, 53, 59, 85, 59, 38, 
	86, 5, 28, 27, 29, 30, 32, 27, 
	86, 30, 5, 88, 14, 15, 16, 89, 
	17, 5, 88, 5, 16, 5, 16, 5, 
	87, 90, 14, 15, 16, 89, 17, 5, 
	16, 5, 16, 5, 87, 5, 91, 92, 
	5, 90, 5, 91, 93, 4, 5, 94, 
	93, 4, 95, 2, 3, 2, 90, 2, 
	5, 96, 97, 5, 88, 14, 15, 16, 
	89, 17, 88, 16, 16, 5, 5, 34, 
	33, 35, 36, 37, 33, 36, 5, 54, 
	53, 55, 39, 56, 57, 53, 56, 38, 
	39, 38, 5, 0
};

static const char _gparcer_trans_targs[] = {
	1, 35, 2, 36, 37, 0, 5, 6, 
	1, 8, 3, 40, 7, 6, 1, 3, 
	40, 7, 7, 41, 9, 11, 12, 43, 
	13, 14, 16, 17, 44, 18, 20, 30, 
	26, 17, 44, 18, 20, 26, 18, 19, 
	17, 44, 18, 20, 26, 20, 21, 20, 
	27, 22, 45, 21, 28, 22, 45, 18, 
	21, 23, 46, 23, 24, 23, 44, 25, 
	26, 23, 27, 26, 44, 25, 23, 27, 
	26, 47, 27, 28, 27, 27, 45, 29, 
	28, 28, 45, 29, 23, 28, 31, 33, 
	42, 4, 34, 34, 2, 38, 39, 38, 
	34, 2
};

static const char _gparcer_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 3, 19, 
	61, 5, 61, 106, 61, 0, 11, 11, 
	46, 11, 0, 0, 3, 0, 0, 7, 
	0, 0, 3, 13, 49, 102, 102, 5, 
	52, 0, 7, 37, 37, 23, 3, 3, 
	9, 40, 90, 90, 43, 3, 74, 74, 
	78, 31, 70, 3, 78, 3, 25, 28, 
	28, 34, 82, 3, 3, 86, 94, 9, 
	0, 90, 90, 98, 64, 0, 37, 37, 
	67, 64, 3, 74, 74, 115, 110, 31, 
	3, 115, 82, 3, 28, 28, 3, 0, 
	0, 21, 0, 15, 15, 15, 15, 0, 
	17, 17
};

static const char _gparcer_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 55, 1, 55, 55, 1, 
	1, 58, 1, 0, 0, 0, 0, 0
};

static const int gparcer_start = 32;
static const int gparcer_first_final = 32;
static const int gparcer_error = 0;

static const int gparcer_en_date = 10;
static const int gparcer_en_gname = 15;
static const int gparcer_en_main = 32;


#line 202 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"


struct m_format fsm;

int format_finish( struct m_format *fsmp )
{
	int result;

	if ( fsmp->cs == format_error )
		result = -1;
	if ( fsmp->cs >= format_first_final && has_return)
		result = 1;
	return result;
}

void format_init( struct m_format *fsm )
{
	buffer_index = 0;
	fsm->buflen = 0;
	fsm->done = 0;
	//int cs, act, have = 0, curline = 1;
	fsm->have = 0;
	fsm->curline = 1;
	fsm->state = 0;
	
#line 287 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
	{
	( fsm->cs) = gparcer_start;
	( fsm->top) = 0;
	}

#line 227 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
}

static int strnum = 0;

int format_execute( struct m_format *fsm, char *data, int len, int isEof )
{
	fsm->curline = ++strnum;
	fsm->buf = data;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	start_tag = data;
	has_return = 0;
	if(len == 0)
		return(0);
	
#line 310 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
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
#line 93 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		append((*( fsm->p)));
	}
	break;
	case 2:
#line 97 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		append((*( fsm->p)));
	}
	break;
	case 3:
#line 102 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{ 
		has_return = 1;
		{( fsm->cs) = ( fsm->stack)[--( fsm->top)]; goto _again;} 
	}
	break;
	case 4:
#line 107 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		{( fsm->stack)[( fsm->top)++] = ( fsm->cs); ( fsm->cs) = 15; goto _again;} 
	}
	break;
	case 5:
#line 111 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		gts = buffer_index;
	}
	break;
	case 6:
#line 115 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_x_coordinate (fsm->curline ,&gBuffer[gts],buffer_index - gts);
	}
	break;
	case 7:
#line 119 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		resetBuffer();
		append((*( fsm->p)));
		b_startCommand(fsm->curline ,fsm->p,1);
		start_tag = fsm->p;
	}
	break;
	case 8:
#line 126 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_g_command (fsm->curline ,start_tag,fsm->p - start_tag);
	}
	break;
	case 9:
#line 130 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_gcomment(fsm->curline ,start_tag,fsm->p - start_tag);
	}
	break;
	case 10:
#line 134 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_o_command (fsm->curline ,fsm->buf,fsm->p - fsm->buf);
//		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
	}
	break;
	case 11:
#line 144 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		h_add_lineNumber(start_tag, fsm->p - start_tag);
		start_tag = fsm->p;
	}
	break;
	case 12:
#line 148 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		start_tag = fsm->p;
	}
	break;
	case 13:
#line 153 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		start_tag = fsm->p;
	}
	break;
	case 14:
#line 157 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		h_comment(start_tag, fsm->p - start_tag);
	}
	break;
#line 474 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
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
#line 88 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		has_return = 1;
		b_endtag();
	}
	break;
	case 9:
#line 130 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_gcomment(fsm->curline ,start_tag,fsm->p - start_tag);
	}
	break;
	case 10:
#line 134 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	{
		b_o_command (fsm->curline ,fsm->buf,fsm->p - fsm->buf);
//		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
	}
	break;
#line 510 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.c"
		}
	}
	}

	_out: {}
	}

#line 243 "/home/walery/workspace_cdt/gcode-lexer/mgParcer.rl"
	
	return (format_finish( fsm ));
}

void init(){
	format_init(&fsm);
}

int execute(char *data, int len){
	fsm.done = 0;
	return(format_execute(&fsm, data, len, true));
}

int finish(){
	return (format_finish(&fsm));
}

