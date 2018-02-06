#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int var_glb; /* A global variable*/

int main(void)
{
    int childPID;
    int var_lcl = 0;
    printf("hello\n");
    childPID = fork();
    printf("\nhello fork\n");
    
    
        
    if(childPID >= 0) // fork was successful//Parent process
    {
        var_lcl = 10;
        var_glb = 20;
        printf("\n Parent process :: var_lcl = [%d], var_glb[%d]\n", var_lcl, var_glb);
    }
    
    else if(childPID == 0) // child process
    {
        var_lcl++;
        var_glb++;
        printf("\n Child Process :: var_lcl = [%d], var_glb[%d]\n", var_lcl, var_glb);
    }

    else // fork failed
    {
        printf("\n Fork failed, quitting!!!!!!\n");
        return 1;
    }
    printf("done\n");
    return 0;
}
