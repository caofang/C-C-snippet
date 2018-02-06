
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;



int main(){

    //char str2[] = "a=1,b=2,c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10";
    char str1[] = "1,1,1,8,8,16,16,1024,1000,100";
    char *strPointer = str1;
    char *strToken;
    int array[10];
    int i;

    cout << strPointer << endl;
//

    strToken = strtok(str1,",");
    i=0;
    while(strToken){

        array[i] = atoi(strToken);
        cout << strToken << "\t" << array[i++] << endl;
        strToken = strtok(NULL,",");
    }

}