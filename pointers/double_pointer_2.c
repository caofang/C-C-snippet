// more pointers
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main ()
{
    int i=0;
    unsigned char *sh_processed = malloc(4096);
    bzero(sh_processed, 4096);
    unsigned char *udp_header = sh_processed + 32;

    unsigned char **master_pointer;
    // unsigned char **master_pointer_tmp = &udp_header;
    master_pointer = sh_processed;
    *master_pointer = udp_header;
    for(i=0;i<16;i++){
        *udp_header = (i + 0xa);
        udp_header++;
    }

    printf("sh_processed: %p\n", sh_processed);
    printf("master_pointer: %p\n",master_pointer);
    printf("*master_pointer: %p\n",*master_pointer);
    printf("**master_pointer: %x\n",**master_pointer);
    printf("udp_header: %p\n", udp_header);
// ------------------- write -------------------------
    printf("\n\n");
    
    unsigned char **master_pointer_read;
    master_pointer_read = sh_processed;

    printf("sh_processed: %p\n", sh_processed);
    printf("master_pointer_read: %p\n",master_pointer_read);
    printf("*master_pointer_read: %p\n",*master_pointer_read);
    printf("**master_pointer_read: %x\n",**master_pointer_read); 






    free(sh_processed);
    return 0;
}