#include <stdio.h>

void a(void (*func)())
{
    func();
}

void func1()
{
    printf("hello world\n");
}

void func2(const void *first_arg, const void *second_arg )
{
    int first = *(int*)first_arg;
    int second = *(int*)second_arg;

    printf("first=%d, second=%d\n",first,second);
}


int main()
{
    int x=1,y=2;
    a(func1);
    
    void (*callback)(const void *var1, const void *var2);
    callback = &func2;
    callback(&x,&y);
    
    func2(&x,&y);
    return 0;
}