CFLAGS=-std=c99
TARGET=hello


json: all.o 
	$(CC) test.o -o test

all.o:
	$(CC) $(CFLAGS) -c test.c
clean: 
	$(RM) test
