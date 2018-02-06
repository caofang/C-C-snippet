// this example continues the pointer examples
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//using namespace std;
#define size 4
int main ()
{
    unsigned short short_array[] = {1,3,8,4095};
    unsigned short * short_pointer;
    unsigned char byte_array[] = {1,20,15,255};
    unsigned char * byte_pointer;
    int i=0;

    unsigned short num = 4095;
    unsigned short endian_swap;
    endian_swap = (num>>8) | (num<<8);

    printf("before:%u, endian_swap:%u\n",num,endian_swap);


    short_pointer = short_array;
    // short_pointer= &short_array[0];
    byte_pointer=&byte_array[0];
    // byte_pointer=byte_array[0];
    for(i=0;i<size;i++){
        printf("short_array addr: %p; value: %u;\tByte_array addr: %p; value: %u;\n",short_pointer,*short_pointer,byte_pointer,*byte_pointer);
        short_pointer++; // now it points to the next position, address = adress + 2 Byte
        //*short_pointer++; // equivalent to above
        //(*short_pointer)++; // increase the the value at pointed loaction

        byte_pointer++;
    }
    printf("\n==============================================================\n");

//========= byte to short ============= 0f ff --> 0fff
    
    printf("type casting, byte to short\n");
    short_pointer = (unsigned short *)byte_array;   //changing byte_array to short pointer
    for(i=0;i<(size>>1);i++){
        printf("short pointer: %p; value: %u;\n",short_pointer,*short_pointer);
        short_pointer++;
    }
    printf("\n");

    printf("endian_swap:\ntype casting, byte to short\n");
    short_pointer = (unsigned short *)byte_array;
    for(i=0;i<(size>>1);i++){
        *short_pointer = (*short_pointer>>8)|(*short_pointer<<8);
        printf("short pointer: %p; value: %u;\n",short_pointer,*short_pointer);
        short_pointer++;
    }
    printf("\n==============================================================\n");

//======= short to byte =========== 0fff --> 0f ff 

    printf("type casting, short to byte\n");
    short_pointer= &short_array[0];
    byte_pointer = (unsigned char *)short_array;
    for(i=0;i<size;i++){
        printf("short_array addr: %p, value: %u\n",short_pointer,*short_pointer);
        printf("Byte_array addr: %p; value: %u;\n",byte_pointer,*byte_pointer);
        byte_pointer++;
        printf("Byte_array addr: %p; value: %u;\n\n",byte_pointer,*byte_pointer);
        byte_pointer++;
        *short_pointer++;
    }
    printf("\n");

    printf("endian_swap:\ntype casting, short to byte\n");
    short_pointer= &short_array[0];
    byte_pointer = (unsigned char *)short_array;
    for(i=0;i<size;i++){
        *short_pointer = (*short_pointer>>8)|(*short_pointer<<8);

        printf("short_array addr: %p, value: %u;\n",short_pointer,*short_pointer);
        printf("Byte_array addr: %p; value: %u;\n",byte_pointer,*byte_pointer);
        byte_pointer++;
        printf("Byte_array addr: %p; value: %u;\n\n",byte_pointer,*byte_pointer);
        byte_pointer++;
        *short_pointer++;

    }

    return 0;
}
