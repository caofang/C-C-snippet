#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;


int cgiPares=0;
//----------------------------------------------------------------------
/** Convert a two-char hex string into the char it represents. **/
char x2c(char *what) {
    register char digit;

    digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
    digit *= 16;
    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
    return(digit);
}

//-------------------------------------------------------------------------
/** Reduce any %xx escape sequences to the characters they represent. **/
void unescape_url(char *url) {
    register int i,j;

    for(i=0,j=0; url[j]; ++i,++j) {
        if((url[i] = url[j]) == '%') {
            url[i] = x2c(&url[j+1]) ;
            j+= 2;
        }
    }
    url[i] = '\0' ;
}

//============================================================================
/** Read the CGI input and place all name/val pairs into list.        **/
/** Returns list containing name1, value1, name2, value2, ... , NULL  **/
char **getcgivars() {

    register int i ;
    char *request_method ;
    int content_length;
    char *cgiinput ;
    char **cgivars ;
    char **pairlist ;
    int paircount ;
    char *nvpair ;
    char *eqpos ;

    // Depending on the request method, read all CGI input into cgiinput.
    request_method= getenv("REQUEST_METHOD") ;
    if (!strcmp(request_method, "GET") || !strcmp(request_method, "HEAD") ) {
        // Some servers apparently don't provide QUERY_STRING if it's empty, 
        //   so avoid strdup()'ing a NULL pointer here.                      
        char *qs ;
        qs= getenv("QUERY_STRING") ;
        cgiinput= strdup(qs  ? qs  : "") ;
    }
    else if (!strcmp(request_method, "POST")) {
        // strcasecmp() is not supported in Windows-- use strcmpi() instead 
        if ( strcasecmp(getenv("CONTENT_TYPE"), "application/x-www-form-urlencoded")) {
            printf("Content-Type: text/plain\n\n") ;
            printf("getcgivars(): Unsupported Content-Type.\n") ;
            exit(1) ;
        }
        if ( !(content_length = atoi(getenv("CONTENT_LENGTH"))) ) {
            printf("Content-Type: text/plain\n\n") ;
            printf("getcgivars(): No Content-Length was sent with the POST request.\n") ;
            exit(1) ;
        }
        if ( !(cgiinput= (char *) malloc(content_length+1)) ) {
            printf("Content-Type: text/plain\n\n") ;
            printf("getcgivars(): Couldn't malloc for cgiinput.\n") ;
            exit(1) ;
        }
        if (!fread(cgiinput, content_length, 1, stdin)) {
            printf("Content-Type: text/plain\n\n") ;
            printf("getcgivars(): Couldn't read CGI input from STDIN.\n") ;
            exit(1) ;
        }
        cgiinput[content_length]='\0' ;
    }
    
    else {
        printf("Content-Type: text/plain\n\n") ;
        printf("getcgivars(): Unsupported REQUEST_METHOD.\n") ;
        exit(1) ;
    }

    // Change all plusses back to spaces.
    for (i=0; cgiinput[i]; i++) if (cgiinput[i] == '+') cgiinput[i] = ' ' ;

    // First, split on "&" and ";" to extract the name-value pairs into 
    //   pairlist.                                                      
    pairlist= (char **) malloc(256*sizeof(char **)) ;
    paircount= 0 ;
    nvpair= strtok(cgiinput, "&;") ;
    while (nvpair) {
        pairlist[paircount++]= strdup(nvpair) ;
        if (!(paircount%256))
        pairlist= (char **) realloc(pairlist,(paircount+256)*sizeof(char **)) ;
        nvpair= strtok(NULL, "&;") ;
    }
    pairlist[paircount]= 0 ;    // terminate the list with NULL

    // Then, from the list of pairs, extract the names and values. 
    cgivars= (char **) malloc((paircount*2+1)*sizeof(char **)) ;
    for (i= 0; i<paircount; i++) {
        if (eqpos=strchr(pairlist[i], '=')) {
            *eqpos= '\0' ;
            unescape_url(cgivars[i*2+1]= strdup(eqpos+1)) ;
        } 
        else {
            unescape_url(cgivars[i*2+1]= strdup("")) ;
        }
        unescape_url(cgivars[i*2]= strdup(pairlist[i])) ;
    }
    cgivars[paircount*2]= 0 ;// terminate the list with NULL

    // Free anything that needs to be freed.
    free(cgiinput) ;
    for (i=0; pairlist[i]; i++) free(pairlist[i]) ;
    free(pairlist) ;

    // Return the list of name-value strings.
    cgiPares = paircount; 
    return cgivars;
}

//======================Passint Parameters of Sensor Size===============================================
int main(){

    printf("\n\n");// for CGI web to read pfintf

    char **cgivars;
    int i,a,b,c;
 
    char configBuff[100];
    unsigned char fileChar[2];


    //=====Get information from CGI========
    /*
    192.168.1.1/cgi-bin/deviceConfig?
    r=1&interpolation=1&sensorX=8&sensorY=8&deviceX=32&deviceY=32&
    bytes=512&Timeout=1000&loops=100&bits=12&gain=4&delay=1&n=1
    */

    /*
     *  sequence is IMPORTANT:

     0   rotation=0 
     1   interpolation=0
     2   sensorX=64
     3   sensorY=32
     4   deviceX=64
     5   deviceY=32
     6   bytes=4096
     7   Timeout=1000
     8   loops=100
     9   bits=12
     10   gain=8
     11  delay=4
     12   n=1

    */
    cgivars= getcgivars(); 
    int rotation;
    int interpolation; 
    int sensorX;
    int sensorY;
    int deviceX;
    int deviceY;
    int BytesRequired;
    int timeout;
    int loops;
    int bits;
    int gain;
    int delay;
    int n;


    remove("/usr/configFile");
    ofstream configFile ("/usr/configFile");
    ofstream ttyACM ("/dev/ttyACM0");

    if(configFile.is_open() && ttyACM.is_open()){
        // write parameters to configFile
        for(i=0; i<cgiPares; i++){
            //cout << cgivars[i*2] << " = " << cgivars[i*2+1] << endl;

            if(!strcmp(cgivars[i*2],"rotation")) {
                rotation = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"interpolation")) {
                interpolation = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"sensorX")) {
                sensorX = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"sensorY")) {
                sensorY = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"deviceX")){
                deviceX = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"deviceY")){
                deviceY = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"bytes")){
                BytesRequired = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"timeout")){
                timeout = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"loops")){
                loops = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"bits")){
                bits = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"gain")){
                gain = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"delay")){
                delay = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            else if(!strcmp(cgivars[i*2],"n")){
                n = atoi(cgivars[i*2+1]);
                configFile << cgivars[i*2] << "=" << cgivars[i*2+1] << endl;
            }
            
        }
        

        // Configurate Box
        //ttyACM << "r" << gain 
        cout << "update successful" << endl;
    }
    else{
        cout << "fail to update" << endl;
    }

    configFile.close();
    ttyACM.close();
    return 0;       
}


