/****************
* Helloworld.cpp
*****************/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include <malloc.h>
#include <stdio.h>

using namespace std;
int i;
int main(int argc,char *argv[])
{

	string str = getenv("QUERY_STRING");
	int strSize = str.size();


	
	cout << "Content-type: text/html" << endl << endl
	<< "<html>" << endl
	<< "<body>" << endl
	<< "<p>" << endl
	<< "Hello! You sent: " << str << endl
	<< "<br>bytes of data which read: " << endl
	<< strSize << endl
	<< "</p>" << endl
	<< "</body>" << endl
	<< "</html>";

	return 0;
}
