#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGX_VERSION "1.1"

const char *LOGX_OUT = "LOGXOUT";
const char *LOGX_TAG = "LOGXTAG";

int main(int argc,char *argv[])
{
    if(argc > 2){
        printf("logx: Too much parameters\n");
        exit (1);
    } else if (argc == 2){
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "version") == 0){
            printf("logx: Version %s\n", LOGX_VERSION);
            exit (0);
        } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0){
            printf("logx: Usage:\n      Set environment variables:\n      \"export %s=<Output file path>\" and \"export %s=<TAG of log sender>\"\n      logx <log>\n", LOGX_OUT, LOGX_TAG);
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
    struct timeval tv;
    
    strftime(buff, 20, "%H:%M:%S", localtime(&now));
    gettimeofday(&tv, NULL);
	
	FILE *fp;
    if((fp=fopen(logx_out, "a+"))==NULL)
    {
        printf("logx: Can not open \"%s\", please check your %s environment variable\n", logx_out, LOGX_OUT);
        exit(1);
    }

    std::string output_string;
    std::string time_now(buff);
    std::string millisecond = std::to_string(tv.tv_usec / 1000);
    output_string = "[" + time_now + "." + millisecond + "] " + logx_tag + " : " + argv[1] + "\n";
    const char* append = output_string.c_str();
	fputs(append,fp);
	fclose(fp);
	return 0;
}