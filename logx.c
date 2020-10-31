#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logx.h"

char *attach(char *, char*);

int main(int argc,char *argv[])
{
    if(argc > 2){
        printf("logx: Too much arguments\n");
        return 1;
    }
    char buff[20];
    time_t now = time(NULL);
    strftime(buff, 20, "%H:%M:%S", localtime(&now));
	
	FILE *fp;
    if((fp=fopen(LOGX_OUT_FILE_NAME,"a+"))==NULL)
    {
        printf("logx: Can not open file\n");
        exit(0);
    }

	char* append = attach(attach("[",attach(&buff,"]")),attach(attach(" ", argv[1]),"\n"));
	fputs(append,fp);
	fclose(fp);
	return 0;
}

char* attach(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
	if (result == NULL) exit (1);
 
    strcpy(result, s1);
    strcat(result, s2);
 
    return result;
}

