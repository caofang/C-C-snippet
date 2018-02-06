/*
    get option from unix command line interface
    program -a -b val
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    // ./program -p 50000 -r /var/www/
    while ((c = getopt (argc, argv, "p:r:")) != -1)
    {
        printf("%c: \t",c);
        switch (c)
        {
            case 'r':
                printf("%s\n",optarg);
                break;
            case 'p':
                printf("%s\n",optarg);
                break;
            case '?':
                printf("Wrong arguments given!!!\n");
                exit(1);
            default:
                exit(1);
        }
    }
    return 0;
}
