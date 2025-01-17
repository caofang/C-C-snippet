#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;


int main(int argc, char **argv)
{
    if (argc < 2){

        printf("USAGE: %s loop-iterations\n", argv[0]);
        return 1;
    }

    int iterations = atoi(argv[1]);
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < iterations; i++){

    }

    gettimeofday(&end, NULL);
    printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)-(start.tv_sec * 1000000 + start.tv_usec)));
    cout << (end.tv_usec - start.tv_usec) << endl;
    cout << start.tv_sec << endl;
    cout << start.tv_usec << endl;
    cout << end.tv_sec << endl;
    cout << end.tv_usec << endl;
    return 0;   
}