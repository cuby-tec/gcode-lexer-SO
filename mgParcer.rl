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


%%{
	machine gparcer;
	
	
	access fsm->;
	variable p fsm->p;
	variable pe fsm->pe;
	variable eof fsm->eof;
	variable cs fsm->cs;
	variable stack fsm->stack;
	variable top fsm->top;
	
	
	optional = (('+'|'-')? digit+ ('.' digit+)?){,1};
	
	decimal = ('+'|'-')? digit+ ('.' digit+)?;
		
	word = alnum*;

	action finish_ok {
		has_return = 1;
		b_endtag();
	}
	
	action dgt      {
		append(fc);
	}
	
	action dec      {
		append(fc);
	}


	action return { 
		has_return = 1;
		fret; 
	}
	
	action call_gblock {
		fcall gname; 
	}
	
	action start_param {
		gts = buffer_index;
	}
	
	action end_param {
		b_x_coordinate (fsm->curline ,&gBuffer[gts],buffer_index - gts);
	}
	
	action start_tag {
		resetBuffer();
		append(fc);
		b_startCommand(fsm->curline ,fsm->p,1);
		start_tag = fsm->p;
	}
	
	action command_index{
		b_g_command (fsm->curline ,start_tag,fsm->p - start_tag);
	}
	
	action end_comment{
		b_gcomment(fsm->curline ,start_tag,fsm->p - start_tag);
	}
	
	action end_otag{
		b_o_command (fsm->curline ,fsm->buf,fsm->p - fsm->buf);
//		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
	}
	
	action end_command{
		b_command(fsm->curline ,start_tag,fsm->p - start_tag);
		
	}
	
	action line_number{
		h_add_lineNumber(start_tag, fsm->p - start_tag);
		start_tag = fsm->p;
	}
	action start_line_number{
		start_tag = fsm->p;
	}
	
	
	action f_comment{
		start_tag = fsm->p;
	}
	
	action fend_comment{
		h_comment(start_tag, fsm->p - start_tag);
	}
	
	
	# A parser for date strings.
	date := decimal  '\n' @return;

	
	gindex = digit+ $dgt ( '.' @dec [0-9]+ $dgt )? ;
	
	#Local commentary
	#l_com = ( (';' (any)* :>> cntrl)) @end_param ;
	#l_com = (( '('(any)* :>> ')') | (';' (any)* :>> cntrl)) @end_param ;
	l_com = (( '('(any)* :>> ')') ) ;
	
	#f_comment = ( (print)+ );
	malpha = [A-Z*];
	
	#param_data = ((malpha) ([+\-]? digit+)? ('.' digit+)? )%end_param ;
	param_data = ((malpha) ([+\-]? digit+)? ('.' digit+)? ) ;
	
	#param = ((param_data) | ( l_com  ) )>start_param $dgt %end_param ;
	param = ((malpha graph*) | ( l_com  ) )>start_param $dgt %end_param ;
	
	# A parser for name strings.
	gname := (( gindex)%command_index space* (param space*)* ((';' print*)>f_comment %fend_comment )* '\n') @return;

	#Comment content
	comment = ( (print)+  ) %end_comment ;
	
	o_tag = ( (any)* :> cntrl ) %end_otag ;
	
	# The main parser.
	block =(('N' gindex)>start_line_number%line_number .' '*)?(  [GMFTS]  @call_gblock |  'O' o_tag 
	| ';' comment  | ('(' (any)* :>> ')')%end_comment )>start_tag;
	
	main := (space* | (extend-ascii)*)  (block (l_com)? '\n'? | ('' '\n')? ) %finish_ok;	
	
	
	
	
}%%

%% write data ;


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
	%% write init;
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
	%% write exec;
	
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

