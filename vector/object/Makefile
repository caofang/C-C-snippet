# 

PROG = circleVector
CC = g++
OBJS = main.o Circle.o
CXXFLAGS=-g -std=c++11
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

main.o:
	$(CC) $(CXXFLAGS) -c main.cpp

Circle.o: Circle.h
	$(CC) $(CXXFLAGS) -c Circle.cpp

clean:
	rm -f core $(PROG) $(OBJS)