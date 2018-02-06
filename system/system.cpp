#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{	
	//char CMD[] = argv[1];
    FILE *cmd=popen(argv[1], "r");
    char result[512]={0x0};
    while (fgets(result, sizeof(result), cmd) !=NULL){
           printf("%s", result);
       }
    pclose(cmd);
    return 0;
}