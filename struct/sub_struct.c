#include <stdio.h>

typedef struct {
  float x, y;
} PDPoint;

typedef struct {
  float width, height;
} PDSize;

typedef struct {
  PDPoint origin;
  PDSize size;
} PDRect;

int main(int argc, char *argv[]) {
    PDRect rect = 
    {
        .origin = 
        {
            .x = 1,
            .y = 1
        },
        .size = 
        {
            .height = .5,
            .width = .5
        }
    };
    printf("w:%f h:%f x:%f y:%f\n",
        rect.size.width,
        rect.size.height,
        rect.origin.x,
        rect.origin.y
        );
    return 0;
}