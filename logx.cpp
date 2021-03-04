#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOGX_VERSION "1.2"

const char *LOGX_OUT = "LOGXOUT";
const char *LOGX_TAG = "LOGXTAG";

int main(int argc,char *argv[])
{
    if(argc > 2){
        std::cout << "logx: Too much parameters" << std::endl;
        exit (1);
    } else if (argc == 2){
        if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "version") == 0){
            std::cout << "logx: Version " << LOGX_VERSION << std::endl;
            exit (0);
        } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0){
            std::cout << "logx: Usage:\n      Set environment variables:\n      \"export " << LOGX_OUT << "=<Output file path>\" and \"export " << LOGX_TAG << "=<TAG of log sender>\"\n      logx <log>" << std::endl;
            exit (0);
        }
    } else if (argc < 2){
        std::cout << "logx: Use \"logx -h\" or \"logx help\" to get help information" << std::endl;
        exit (1);
    }
    
    char *logx_out = getenv(LOGX_OUT);
    char *logx_tag = getenv(LOGX_TAG);
    int env_status = 0;
    if(logx_out == NULL){
      std::cout << "logx: error: " << LOGX_OUT <<" is " << logx_out << "\nPlease use \"export " << LOGX_OUT << "=<Output file path>\" to set this environment variable" << std::endl;
      env_status = -1;
    }
    if(logx_tag == NULL){
      std::cout << "logx: error: " << LOGX_TAG << " is " << logx_tag << "\nPlease use \"export " << LOGX_TAG << "=<TAG of log sender>\" to set this environment variable" << std::endl;
      env_status = -1;
    }
    if(env_status){
      std::cout << "\nlogx: Some environment variables are not set, please fix above errors and retry" << std::endl;
      exit(1);
    }
	
	FILE *fp;
    if((fp=fopen(logx_out, "a+"))==NULL)
    {
        std::cout << "logx: Can not open \"" << logx_out << "\", please check your " << LOGX_OUT << " environment variable" << std::endl;
        exit(1);
    }
    
    char buff[16];
    time_t now = time(NULL);
    struct timeval tv;
    
    strftime(buff, 16, "%m-%d %H:%M:%S", localtime(&now));
    gettimeofday(&tv, NULL);
    
    std::string output_string;
    std::string time_now(buff);
    std::string millisecond = std::to_string(tv.tv_usec / 1000);
    output_string = "[" + time_now + "." + millisecond + "] " + logx_tag + " : " + argv[1] + "\n";
    const char* append = output_string.c_str();
	fputs(append,fp);
	fclose(fp);
	return 0;
}