CFLAGS=-std=c99
TARGET=point_example


json: all.o 
	$(CC) -o $(TARGET) point_example.o

all.o:
	$(CC) $(CFLAGS) -c point_example.c
clean: 
	$(RM) $(TARGET) point_example.o
