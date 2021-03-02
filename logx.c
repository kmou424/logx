#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGX_VERSION "1.0"

const char *LOGX_OUT = "LOGXOUT";
const char *LOGX_TAG = "LOGXTAG";

char *attach(char *, char*);

int main(int argc,char *argv[])
{
    if(argc > 2){
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
    } else if (argc < 2){
        printf("logx: Use \"logx -h\" or \"logx help\" to get help information\n");
        exit (1);
    }
    
    char *logx_out = getenv(LOGX_OUT);
    char *logx_tag = getenv(LOGX_TAG);
    int env_status = 0;
    if(logx_out == NULL){
      printf("logx: error: %s is %s\nPlease use \"export %s=<Output file path>\" to set this environment variable\n", LOGX_OUT, logx_out, LOGX_OUT);
      env_status = -1;
    }
    if(logx_tag == NULL){
      printf("logx: error: %s is %s\nPlease use \"export %s=<TAG of log sender>\" to set this environment variable\n", LOGX_TAG, logx_tag, LOGX_TAG);
      env_status = -1;
    }
    if(env_status){
      printf("\nlogx: Some environment variables are not set, please fix above errors and retry\n");
      exit(1);
    }
    
    char buff[20];
    time_t now = time(NULL);
    strftime(buff, 20, "%H:%M:%S", localtime(&now));
	
	FILE *fp;
    if((fp=fopen(logx_out, "a+"))==NULL)
    {
        printf("logx: Can not open \"%s\", please check your %s environment variable\n", logx_out, LOGX_OUT);
        exit(1);
    }

	char* append = attach(attach("[",attach(&buff,"]")),attach(attach(" ", attach(logx_tag, attach(": ", argv[1]))),"\n"));
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

