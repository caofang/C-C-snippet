
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <regex.h>

#define config_file_path "file/device_config"

int regex_check(char *test_string,char *format);

int main(int argc, char *argv[]){
    

    FILE *config_file;
    char *file_string;
    size_t len = 0;
    ssize_t read;
    char *line = NULL;


    config_file = fopen(config_file_path,"r");
    if (config_file == NULL){
        perror("Fail to open config_file\n");
    }

    
    read = getline(&line, &len, config_file); 
    printf("%s\n",line);

    read = getline(&line, &len, config_file); 
    printf("%s\n",line);
    char *str1 = strstr(line,"serial=");
    printf("%s\n",str1);

    read = getline(&line, &len, config_file); 
    printf("%s\n",line);
    int check = regex_check(line,"transformation=[0-9]");
    if(check){
        printf("match\n");
    }
    else{
        printf("no match\n");
    }
    
    return 0;
}

int regex_check(char *test_string,char *format){

    regex_t regex;
    int reti;
    char *str;

/* Compile regular expression */
    reti = regcomp(&regex,format, 0);
    if( reti ){ 
        fprintf(stderr, "Could not compile regex\n");
    }

/* Execute regular expression */
    reti = regexec(&regex, test_string, 0, NULL, 0);
    if( !reti ){
        return 1;
    }
    else if( reti == REG_NOMATCH ){
        return 0;
    }
    else{
        regerror(reti, &regex, str, sizeof(str));
        fprintf(stderr, "Regex match failed: %s\n", str);
    }
    /* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);
}