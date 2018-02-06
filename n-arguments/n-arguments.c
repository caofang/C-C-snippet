// this program shows how to pass n arguments to a fuction
// libraty: sdtarg.h
// va_list, va_start, va_arg, va_end


#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

// test function 1
double multiArguments_1(int n, ...){
    va_list argc;
    va_start(argc, n);
    double sum=0;
    double average=0;
    int i;
    for (i=0; i<n; i++){
        printf("arg: %s\n",va_arg(argc, unsigned char*));
    }
    va_end(argc);
    return 0;
}

// test function 2
double multiArguments_2(int n, unsigned char *hello, ...){
    va_list argc;
    va_start(argc, n);

    double sum=0;
    double average=0;
    int i;
    for (i=0; i<n; i++){
        printf("arg: %s\n",va_arg(argc, unsigned char*));
    }
    va_end(argc);
    return 0;
}


int main(int argc, unsigned char * argv[]){
    printf("function(int n, ...)\n");
    multiArguments_1(4, "hello", "world", "joke", "haha");
    printf("function(int n, type arg_1, ...)\n");
	multiArguments_2(3, "hello", "world", "joke", "haha");
}