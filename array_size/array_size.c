#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

int main(){
    unsigned char arr[10];
    printf("10: %d\n", sizeof(arr));
    arr[50];
    printf("50: %d\n", sizeof(arr));


    return 0;
}