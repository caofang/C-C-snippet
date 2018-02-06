
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <regex.h>



#define config_file_path "file/device_config"


void comp_str(){

}

int main(){

    FILE *config_file;
    char *file_string;
    size_t len = 0;
    ssize_t read;
    char *line = NULL;



    char * str1;
    char * str2;
    char *num;

    config_file = fopen(config_file_path,"r");
    if (config_file == NULL){
        perror("Fail to open config_file\n");
    }

    
    read = getline(&line, &len, config_file); 
    printf("file string: %s\n",line);

    read = getline(&line, &len, config_file); 
    printf("file string: %s\n",line);

    str1 = strtok(line,"=");
    printf("%s\n",str1);
    str2 = strtok (NULL,"=\n");
	printf("%s\n",str2);    


}