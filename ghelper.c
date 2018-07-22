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

void h_comment(char* data, size_t len){
	memcpy(sgcode.comment, data, (len<79)?len:79);
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
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}

//void b_y_coordinate(size_t curline, char * param, size_t len)
void b_o_command (size_t curline, char * param, size_t len) // O command
{
    struct sGparam *pr =  &sgcode.param[sgcode.param_number];
    ghelper_setParam(pr,param,len);
    sgcode.param_number++;
}



void
b_startCommand(size_t curline, char * param, size_t len)
{
	memset(&sgcode,0,sizeof(struct sGcode));
	sgcode.group = *param;
	if(lineNumber.group>0)
	{
		sgcode.line =   atoi(lineNumber.value);
	}else{
		sgcode.line = curline;
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
	printf("=================\n");
	printf("_h_report: line number:%i  \tgroup:%c \tindex:%s \tcomment:%s \n",sgcode.line,sgcode.group,sgcode.value , sgcode.comment);
	for(int i=0;i<sgcode.param_number;i++)
	{
		struct sGparam *param = &sgcode.param[i];
		printf("\t_h_param: group:%c \tvalue:%s\n",param->group,param->value);
	}

	printf("=================\n");

	lineNumber.group = 0;

}

