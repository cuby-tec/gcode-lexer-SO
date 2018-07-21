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

//static gfunction parser_out;

 void command (size_t curline, char * param, size_t len);
 void gcomment (size_t curline, char * param, size_t len);
 void g_command (size_t curline, char * param, size_t len);
 void x_coordinate(size_t curline, char * param, size_t len);
 void o_command (size_t curline, char * param, size_t len);
void start_command(size_t curline, char * param, size_t len);//eStartCommand

//void h_add_lineNumber(char* param, size_t len);

 //fprintf(flog, "symbol(%i): %c\n", fsm->curline, fsm->ts[0] );
// void gpunct(size_t curline, char * param, size_t len);

gfunction prs[] = {&command,&gcomment,&g_command,&x_coordinate, &o_command
		, &start_command };


#define gBUFFER_SIZE	100 
 
 char gBuffer[gBUFFER_SIZE];
 
 size_t buffer_index = 0;
 size_t param_index;
 size_t gts;
 char* start_tag;

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
//		if ( fsm->buflen > 0 )
//			fsm->write( fsm->buf, fsm->buflen );
//		fwrite("End\n",1,4,stdout);
		b_endtag();
		printf("\n action finish_ok.\n");
	}
	
	action dgt      {
		append(fc);
//		printf("DGT: %c\n", fc); 
	}
	
	action dec      {
		append(fc);
//		printf("DEC: .\n"); 
	}


	action return { printf("RETURN\n"); fret; }
	
	action call_gblock {
//		append(fc);
//		printf("NAME: %c\n",fc);
		fcall gname; 
	}
	
	action start_param {
		gts = buffer_index;
		printf("start param: %c\n",fc); 
	}
	
	action end_param {
		(*prs[eXparam])(fsm->curline ,&gBuffer[gts],buffer_index - gts);
		fwrite( &gBuffer[gts], 1, buffer_index - gts, stdout );
		printf("\n\tend_param: %c\n",fc); 
	}
	
	action start_tag {
		resetBuffer();
		append(fc);
		//printf("start_tag: %c\n",fc);
		(*prs[eStartCommand])(fsm->curline ,fsm->p,buffer_index);
	}
	
	action command_index{
//		(*prs[eGcommand])(fsm->curline ,gBuffer,buffer_index-gts);
		fwrite( gBuffer, 1, buffer_index, stdout );
		printf("\ncommand_index: %c\n",fc);
	}
	
	action end_comment{
		(*prs[eComment])(fsm->curline ,start_tag,fsm->p - start_tag);
//		printf("end_comment>\n");
//		fwrite( start_tag, 1, fsm->p - start_tag, stdout );
//		printf("\nend_comment: %c\n",fc);
	}
	
	action end_otag{
		(*prs[eOcommand])(fsm->curline ,fsm->buf,fsm->p - fsm->buf);
		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
		printf("\nend_otag: %c\n",fc);
	}
	
	action end_command{
//		/eCommand  start_tag, 1, fsm->p - start_tag, stdout
		(*prs[eCommand])(fsm->curline ,start_tag,fsm->p - start_tag);
		
	}
	
	action line_number{
//		void h_add_lineNumber(char* param, size_t len)
		h_add_lineNumber(fsm->buf, fsm->p - fsm->buf);
//		fwrite( fsm->buf, 1, fsm->p - fsm->buf, stdout );
//		printf("\tline_number: %i\n",fc);
		start_tag = fsm->p;
	}
	
	
	# A parser for date strings.
	date := decimal  '\n' @return;

	
	gindex = digit+ $dgt ( '.' @dec [0-9]+ $dgt )? ;
	
	#Local commentary
	#l_com = ( (';' (any)* :>> cntrl)) @end_param ;
	#l_com = (( '('(any)* :>> ')') | (';' (any)* :>> cntrl)) @end_param ;
	l_com = (( '('(any)* :>> ')') ) ;
	
	#f_comment = ( (print)+ );
	malpha = [A-Za-z*];
	
	#param_data = ((malpha) ([+\-]? digit+)? ('.' digit+)? )%end_param ;
	param_data = ((malpha) ([+\-]? digit+)? ('.' digit+)? ) ;
	
	param = ((param_data) | ( l_com  ) )>start_param $dgt %end_param ;
	f_comment = (';' (print)* )?;
	
	# A parser for name strings.
	gname := (( gindex)%command_index space+ ((( (param) space+ )*)?   )( print*) '\n') @return;

	#Comment content
	comment = ( (print)+  ) %end_comment ;
	
	o_tag = ( (any)* :> cntrl ) %end_otag ;
	
	# The main parser.
	block =(('N' gindex)%line_number .' '*)?( ( 'G'|'M' )  @call_gblock |  'O' o_tag | (extend-ascii)*
	| ('F' gindex )%command_index | ('T' gindex) | 'S' gindex 
	| ';' comment  | ('(' (any)* :>> ')')%end_comment )>start_tag;
	
	main := space*(block (l_com)? '\n'? | ('' '\n')? ) %finish_ok;	
	
	
	
	
}%%

%% write data ;


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
	%% write init;
}
static int strnum = 0;
int format_execute( struct format *fsm, char *data, int len, int isEof )
{
//	const char *p = data;
//	const char *pe = data + len;
//	const char *eof = isEof ? pe : 0;
	fsm->curline = ++strnum;
	fsm->buf = data;
	fsm->p = data;
	fsm->pe = data+len;
	fsm->eof = isEof ? fsm->pe : 0;
	start_tag = data;
	printf("format_execute[892]: len:%d  done:%d line:%d \n",len,fsm->done,fsm->curline);
	if(len == 0)
		return(0);
	%% write exec;
	
		if ( format_finish( fsm ) <= 0 ){
//			int as = 1;
			printf("[898] FAIL :finish code:%d  %-10s \n", format_finish( fsm ) ,data);
			assert(format_finish( fsm ) >= 1) ;
		}

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