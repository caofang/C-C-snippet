# build an executable named hello from main.c lib.c lib.h
CFLAGS=-std=c99
CFLAGS+= -D LIB
TARGET=hello


hello:all.o
	$(CC) main.o lib.o -o $(TARGET)

all.o:
	$(CC) $(CFLAGS) -c main.c lib.c

clean:
	$(RM) $(TARGET) $(TARGET).* *.o
