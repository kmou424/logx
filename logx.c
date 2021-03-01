#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGX_VERSION "1.0"

char *attach(char *, char*);

int main(int argc,char *argv[])
{
    if(argc > 4){
        printf("logx: Too much parameters\n");
        exit (1);
    } else if (argc == 2){
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "version") == 0){
            printf("%s", attach(attach("logx: Version ", LOGX_VERSION), "\n"));
            exit (0);
        } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0){
            printf("logx: Usage:\n      logx <log file path> <TAG> <log>\n");
            exit (0);
        }
    } else if (argc < 4){
        printf("logx: Too few parameters\n");
        exit (1);
    }
    char buff[20];
    time_t now = time(NULL);
    strftime(buff, 20, "%H:%M:%S", localtime(&now));
	
	FILE *fp;
    if((fp=fopen(argv[1],"a+"))==NULL)
    {
        printf("logx: Wrong parameters, can not open file\n");
        exit(1);
    }

	char* append = attach(attach("[",attach(&buff,"]")),attach(attach(" ", attach(argv[2], attach(": ", argv[3]))),"\n"));
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

