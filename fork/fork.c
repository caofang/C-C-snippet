#include <stdio.h>
int num = 0;
int main(int argc, char*argv[]){
	int main_var = 10;
	printf("main entry point, main var: %d\n", main_var);
    int pid = fork();
	if (pid > 0)
	{
		main_var = 1;
	    printf("I'm the parent with pid: %d, and created child with %d, main var: %d\n", getpid(), pid,main_var);
	}
	else if (pid == 0)
	{
		main_var = 20;
	    printf("\nI'm the daughter with pid: %d and parent is %d, main_var: %d\n", getpid(), getppid(), main_var);
	}
	else // pid == -1
	{
	    printf("fork() failed\n");
	}
}
