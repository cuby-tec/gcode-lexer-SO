#include "ghelper.h"
#include <string.h>
#include <stdio.h>

//--------------------- vars

struct sGcode sgcode;

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
	fwrite( &sgcode.group, 1, len, stdout );
	printf("\n\tStart command: curline:%li \n ",curline);


}
