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

unsigned char *file_value(unsigned char *parameter)
{
    unsigned char *value;
    int i;

    char line[64];
    unsigned char file_data[512];
    bzero(file_data,512);
    int total_line=0;

    FILE *config_file;
    config_file = fopen (config_file_path , "r");
    if (config_file == NULL) return 0;
    else{ 
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
        unsigned char *parameterValueP;
        unsigned char *tmp;        
        parameterValueP = strstr(file_data, parameter) + strlen(parameter) + 1;
        tmp = strchr(parameterValueP,0xa);  // look line feed for the end of value
        int difference = tmp - parameterValueP;
        printf("diff: %d\n",difference);
        for (i=0; i<difference; i++){
            *(value + i) = *(parameterValueP +i);
        }
        // memcpy(value,parameterValueP,tmp - parameterValueP);
        value[tmp - parameterValueP] = 0;
        
        printf("%s: %s\n",parameter,value); 

    }    
    return value;
}

int main(int argc, unsigned char *argv[]){
    int i,j,a,b,c,x,y,z;

    unsigned char *value;    

    strcpy(value,file_value(argv[1]));
    printf("%s: %s\n",argv[1], value);

    // printf("%d\n", atoi(file_value(argv[1]))); /// does not work


}



























