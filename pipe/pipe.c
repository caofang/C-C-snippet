#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *shell_script(unsigned char *result, int size, unsigned char *command)
{
    int iUsed = 0;
    FILE *cmd = popen(command, "r");
    *result = '\0';
    if (cmd == NULL){
        return NULL;
    }
    while (fgets(result+iUsed, size - iUsed, cmd) != NULL)
    {
        iUsed += strlen(result + iUsed);
        if (iUsed == size)
            break;
    }
    pclose(cmd);
    return result;
}

int main()
{
    unsigned char cmd[]="ls";
    unsigned char result[512];
    shell_script(result, sizeof(result),cmd);
    printf("result:\n%s\n",result);
    return 0;
}