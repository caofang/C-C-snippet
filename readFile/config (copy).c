/*
    this program reads config_file with specific format
    and parses the data 

    call the program:
        config parameter_name
        the parameter value will be displyed
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define config_file_path "config_file/config_file"
unsigned char *file_value(unsigned char *parameter_name)
{
    unsigned char *parameter_value;
    int i;
    
    return parameter_value;
}

int main(int argc, unsigned char *argv[]){
    int i,j,a,b,c,x,y,z;

    unsigned char parameter[16];
    strcpy(parameter, argv[1]);


    char line[64];
    unsigned char file_data[512];
    bzero(file_data,512);
    int total_line=0;

    FILE *config_file;
    config_file = fopen (config_file_path , "r");
    if (config_file == NULL) perror ("Error opening file");
    else{
// debug
        printf("config_file opened\n");
// 
        while(fgets(line,64,config_file)){
            total_line++;
            strcat(file_data,line);
        }
// debug

        printf("file size: %d, line: %d\n",strlen(file_data), total_line);
        printf("file data:\n%s\n",file_data); 
        // for(i=0;i<strlen(file_data);i++){
        //     printf("%x,",*(file_data+i)); 
        // }
// 
        unsigned char value[16];
        unsigned char *parameterValueP;
        unsigned char *tmp;
        
        parameterValueP = strstr(file_data, parameter) + strlen(parameter) + 1;
        tmp = strchr(parameterValueP,0xa);  // look line feed for the end of value
        memcpy(value,parameterValueP,tmp - parameterValueP);
        value[tmp - parameterValueP] = 0;
// debug        
        printf("s/n_char: %s\n",value); 
        printf("s/n_int: %d\n",atoi(value));
// 
    }
}


