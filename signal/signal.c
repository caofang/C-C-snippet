// #include <signal.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <time.h>

// int done = 0;

// void term(int signum)
// {
//     if (signum == 15)
//     {   
//         //printf("%d\n",signum);        
//         printf("Received SIGTERM, exiting ... \n");
//         done  = 1;
//     }
//     else
//     {
//         time_t mytime = time(0);
//         printf("%d: %s\n", signum, asctime(localtime(&mytime)));
//         printf("%d\n",signum);
//     }
// }

// int main(int argc, char *argv[])
// {
//     struct sigaction action;
//     memset(&action, 0, sizeof(struct sigaction));
//     action.sa_handler = term;
//     sigaction(SIGTERM, &action, NULL);

//     struct sigaction act;
//     memset(&act, 0, sizeof(struct sigaction));
//     act.sa_handler = SIG_IGN;
//     sigaction(SIGQUIT, &act, NULL);
//     sigaction(SIGINT, &act, NULL);

//     int loop = 0;
//     char *s = "hello world";
//     while(!done)
//     {
//         printf("hello\n");
//         sleep(1);
//         *s = 'H';
//     }

//     printf("done.\n");
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void catch_function(int signo) 
{
    printf("signal caught: %d\n", signo);
    exit(0);
}

int main(void) 
{

    signal(SIGINT , catch_function);
    char *s = "hello world";
    char x=1,y;
    x--;
    while(1) 
    {
        printf("Going to sleep for a second...\n");
        sleep(1);
        y = 3/x;
        //*s = 'H';
    }

    // ===== Segmentation fault (core dumped) =====
    // Writing to read-only memory
    // char *s = "hello world";
    

    //  if (signal(SIGSEGV, catch_function) == SIG_ERR) {
    //     fputs("An error occurred while setting a signal handler.\n", stderr);
    //     return EXIT_FAILURE;
    // }
    // *s = 'H';

    // _____ Segmentation fault (core dumped) _____

    // ===== Floating point exception (core dumped) =====
    // char x=1;
    // x--;
    // char y = 3/x;
    // _____ Floating point exception (core dumped) _____

    return 0;
}