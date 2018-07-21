#include "ghelper.h"
#include <string.h>
#include <stdio.h>

//--------------------- vars

struct sGcode sgcode;
struct sGparam lineNumber = {0,{0}};
//----------------------- function


struct sGcode* getSgcode()
{
    return &sgcode;
}

void ghelper_setParam(struct sGparam *pr, char * param, size_t len)
{
//    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    pr->group = param[0];
    strncpy(pr->value,param+1,(len<10)?len-1:9);
    pr->value[(len<10)?len-1:9] = '\0';

//    printf("_h_setParam: grp:%c  val:%s \n",pr->group, pr->value);

}

// Очистка полей для новыъх данных
void clear_sgcode()
{
    struct sGparam* param;

    memset(sgcode.comment,0,sizeof(sgcode.comment));
    sgcode.group = ' ';
    sgcode.line = 0;
    sgcode.param_number = 0;

    //sgcode.value = 0;
    memset(sgcode.value,0,sizeof(sgcode.value));

    for(int i=0;i<sizeof(sgcode.param);i++)
    {
        param = &sgcode.param[i];
        param->group = ' ';
        //param->value
        memset(param->value,0,sizeof(param->value));
    }

}

// It's an End of build command.
void b_command (size_t curline, char * param, size_t len)
{
    sgcode.line = curline;
}

void b_gcomment (size_t curline, char * param, size_t len)
{
//sgcode.comment
    memcpy(sgcode.comment, param, (len<79)?len:79);
//    printf("_h_Comment: %s",sgcode.comment);
}

void b_g_command (size_t curline, char * param, size_t len)
{
//    char buf;
//     'G':
        sgcode.group = param[0];
        strncpy(sgcode.value,&param[1],(len<10)?len-1:9);
        sgcode.value[len-1] = '\0';

}

void b_x_coordinate(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//    pr->group = param[0];
//    strncpy(pr->value,param+1,(len<10)?len-1:9);
//    pr->value[(len<10)?len-1:9] = '\0';
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

//void b_y_coordinate(size_t curline, char * param, size_t len)
void b_o_command (size_t curline, char * param, size_t len) // O command
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//    pr->group = param[0];
//    strncpy(pr->value,param+1,(len<10)?len-1:9);
//    pr->value[(len<10)?len-1:9] = '\0';
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}



void
b_startCommand(size_t curline, char * param, size_t len)
{
	memset(&sgcode,0,sizeof(struct sGcode));
	sgcode.group = *param;
//	fwrite( &sgcode.group, 1, len, stdout );

//	printf("_h_startc linenumber.group:%c \n",lineNumber.group);
	if(lineNumber.group>0)
	{
		//add param
//		struct sGparam *dst = &sgcode.param[sgcode.param_number];
//		dst->group = lineNumber.group;
//		strcpy(dst->value,lineNumber.value);
//		sgcode.param_number++;
		sgcode.line =   atoi(lineNumber.value);
	}else{
		sgcode.line = curline;
	}

//	printf("\n\t_h_Start command: curline:%li \n ",curline);


}

void
h_add_lineNumber(char* param, size_t len)
{
//	 struct sGparam *pr =  &sgcode.param[sgcode.param_number];
//	 ghelper_setParam(pr,param, len);
//	 sgcode.param_number++;

//	ghelper_setParam(&lineNumber,param,len);


	lineNumber.group = param[0];
	strncpy(lineNumber.value,param+1,(len<10)?len-1:9);

//	printf("\t_h_Line number: group:%c  value:%s \n ", lineNumber.group, lineNumber.value);
}


void
b_endtag()
{
	printf("=================\n");
	printf("_h_report: line number:%i  \tgroup:%c  \tcomment:%s \n",sgcode.line,sgcode.group , sgcode.comment);
	for(int i=0;i<sgcode.param_number;i++)
	{
		struct sGparam *param = &sgcode.param[i];
		printf("\t_h_param: group:%c \tvalue:%s\n",param->group,param->value);
	}

	printf("=================");

	lineNumber.group = 0;

}

