#include "ghelper.h"
#include <string.h>
#include <stdio.h>

//--------------------- vars

struct sGcode* dst;

struct sGparam lineNumber = {0,{0}};
//----------------------- function


struct sGcode* getSgcode()
{
    return dst;
}

void ghelper_setParam(struct sGparam *pr, char * param, size_t len)
{
//    struct sGparam *pr =  &dst->param[dst->param_number];
    pr->group = param[0];
    strncpy(pr->value,param+1,(len<10)?len-1:9);
    pr->value[(len<10)?len-1:9] = '\0';

//    printf("_h_setParam: grp:%c  val:%s \n",pr->group, pr->value);

}

// Очистка полей для новыъх данных
void clear_sgcode()
{
    struct sGparam* param;

    memset(dst->comment,0,sizeof(dst->comment));
    dst->group = ' ';
    dst->line = 0;
    dst->param_number = 0;

    //dst->value = 0;
    memset(dst->value,0,sizeof(dst->value));

    for(int i=0;i<sizeof(dst->param);i++)
    {
        param = &dst->param[i];
        param->group = ' ';
        //param->value
        memset(param->value,0,sizeof(param->value));
    }

}

// It's an End of build command.
void b_command (size_t curline, char * param, size_t len)
{
    dst->line = curline;
}

void b_gcomment (size_t curline, char * param, size_t len)
{
//dst->comment
    memcpy(dst->comment, param, (len<79)?len:79);
//    printf("_h_Comment: %s",dst->comment);
}

void h_comment(char* data, size_t len){
	memcpy(dst->comment, data, (len<79)?len:79);
}

void b_g_command (size_t curline, char * param, size_t len)
{
//    char buf;
//     'G':
        dst->group = param[0];
        strncpy(dst->value,&param[1],(len<10)?len-1:9);
        dst->value[len-1] = '\0';

}

void b_x_coordinate(size_t curline, char * param, size_t len)
{
    struct sGparam *pr =  &dst->param[dst->param_number];
    ghelper_setParam(pr,param,len);
    dst->param_number++;
}

//void b_y_coordinate(size_t curline, char * param, size_t len)
void b_o_command (size_t curline, char * param, size_t len) // O command
{
    struct sGparam *pr =  &dst->param[dst->param_number];
    ghelper_setParam(pr,param,len);
    dst->param_number++;
}



void
b_startCommand(size_t curline, char * param, size_t len)
{
	memset(dst,0,sizeof(struct sGcode));
	dst->group = *param;
	if(lineNumber.group>0)
	{
		dst->line =   atoi(lineNumber.value);
	}else{
		dst->line = curline;
	}
}

void
h_add_lineNumber(char* param, size_t len)
{
	lineNumber.group = param[0];
	strncpy(lineNumber.value,param+1,(len<10)?len-1:9);
}


void
b_endtag()
{
//	printf("=================\n");
//	printf("_h_report: line number:%i  \tgroup:%c \tindex:%s \tcomment:%s \n",dst->line,dst->group,dst->value , dst->comment);
//	for(int i=0;i<dst->param_number;i++)
//	{
//		struct sGparam *param = &dst->param[i];
//		printf("\t_h_param: group:%c \tvalue:%s\n",param->group,param->value);
//	}
//
//	printf("=================\n");
//
	lineNumber.group = 0;

}

