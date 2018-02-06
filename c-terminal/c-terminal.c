/*
    c terminal program
	it forks a process and opens a pipe to execute shell cmd and read back outputs

    if the program is copied to /www/cgi-bin it can take url arguments

    instuctions
        c-terminal ls
        c-terminal ls\ -l       


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *shell_script(unsigned char *parameter){
    unsigned char *outputs;
    unsigned char result[1024];
    outputs = malloc(16384);
    bzero(outputs,16384);
    bzero(result,1024);
    printf("argv: %s\n", parameter);

    // access shell script
    FILE *cmd=popen(parameter, "r");
    while (fgets(result, sizeof(result), cmd) !=NULL){
        strcat(outputs,result);
    }
    pclose(cmd);
    return outputs;
}

int main(int argc, char *argv[])
{   
    int i,j,x,y,z;
    unsigned char cmd_1[64];
    if(argc <= 1){
        printf("No Argument\n");
    }
    else if(argc > 1){
        printf("argv[1]: %s, %d\n", argv[1],strlen(argv[1]));
        unsigned char cmd_1[64] = {0};
        unsigned char *msg;
        if (!argv[2]){
                printf("no shell argument\n");
        }
        else{
            strcpy(cmd_1,argv[1]);
            // strcpy(cmd_1,argv[2]);
            // for(i=3; i<argc; i++){
            for(i=2; i<argc; i++){
                strcat(cmd_1," ");
                strcat(cmd_1,argv[i]);
            }
            printf("%s, %d\n",cmd_1,argc);
            msg = shell_script(cmd_1);
            printf("%s\n",msg);
            
        }
    }

    return 0;
}

