// more pointers
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define size 4
int main ()
{
    int a=1;
    int b=2;
    printf("a:%d, b:%d\n",a,b);
    swap(a,b);
    printf("a:%d, b:%d\n",a,b);

    unsigned short short_array[] = {1,3,8,4095};
    unsigned short * short_pointer;
    unsigned char byte_array[] = {1,20,15,255};
    unsigned char * byte_pointer;
    int i=0;
    short_pointer = short_array;
    // short_pointer= &array[0];
    for(i=0;i<size;i++){
        printf("short pointer: %p; value: %u;\n",short_pointer,*short_pointer);
        //short_pointer++; // now it points to the next position, address = adress + 2 Byte
        *short_pointer++; // equivalent to above
        //(*short_pointer)++; // increase the the value at pointed loaction
    }
    printf("\n");

    byte_pointer=&byte_array[0];
    // byte_pointer=byte_array[0];
    for(i=0;i<size;i++){
        printf("Byte pointer: %p; value: %u;\n",byte_pointer,*byte_pointer);
        byte_pointer++;
    }
    printf("\n");


    printf("type casting, byte to short\n");
    short_pointer = (unsigned short *)byte_array;
    for(i=0;i<(size>>1);i++){
        printf("short pointer: %p; value: %u;\n",short_pointer,*short_pointer);
        short_pointer++;
    }
    printf("\n");


    printf("type casting, short to byte\n");
    byte_pointer = (unsigned char *)short_array;
    for(i=0;i<(size*2);i++){
        printf("short pointer: %p; value: %u;\n",byte_pointer,*byte_pointer);
        byte_pointer++;
    }
    printf("\n");
    
    return 0;
}