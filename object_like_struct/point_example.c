
// gcc -o point_example point_example.c


#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// struct point

typedef struct point 
{
    int x;
    int y;
    void (*set_xy)(struct point* p, int x, int y);
    void (*print)(struct point* );
    void (*test)();

}PointObject;

// typedef struct point PointObject;
void print(struct point* p);
void set_xy(struct point* p, int x, int y);

void test()
{
	printf("test\n");
}

PointObject* Object_new() { 
	PointObject* p = malloc(sizeof(PointObject));
	if (p != 0)
	{
	    p->set_xy = set_xy;
	    p->print = print;
	    p->test = test;

	    p->x = 0;
	    p->y = 0;
	}

  return p;
}

/* Methods */

void print(struct point* p)
{
    printf("x=%d\n", p->x);
    printf("y=%d\n", p->y);
}

void set_xy(struct point* p, int x, int y)
{
    if (p != NULL)
    {    
        p->x = x;
        p->y = y;
    }
}

int main(void)
{
    PointObject* p3 = Object_new();
    p3->set_xy(p3, 1,2);
    p3->print(p3);

    print(p3);


    p3->test();

    test();

    return 0;
}