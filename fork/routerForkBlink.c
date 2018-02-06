#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int var_glb; /* A global variable*/

int main(void)
{
    int PID;
    int i;
    int var_lcl = 0;
    int fd;

    PID = fork();
    if(PID == 0){
        // child
        fd = open("/sys/class/gpio/gpio8/value", O_RDWR); 
        for(;;){
            write(fd,"1",1);
            sleep(1);
            write(fd,"0",1);
            sleep(1);
        }

    }
    else if(PID > 0){
        // parent
        for(i=0;i<10;i++){
            sleep(1);
        }
        kill(PID,SIGKILL);

    }

    
    /*
    
    if(PID >= 0) // fork was successful
    {
        if(PID == 0) // child process
        {

        }
        else //Parent process
        {

        }
    }
    else // fork failed
    {
        printf("\n Fork failed, quitting!!!!!!\n");
        return 1;
    }
    printf("done\n");
    */
    close(fd);
    return 0;
}
