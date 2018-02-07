# 

PROG = circleVector
CC = g++
OBJS = main.o Circle.o Subject.o Radius.o
CXXFLAGS=-g -std=c++11
$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

main.o:
	$(CC) $(CXXFLAGS) -c main.cpp

Circle.o: Circle.h
	$(CC) $(CXXFLAGS) -c Circle.cpp

Subject.o: Subject.h
	$(CC) $(CXXFLAGS) -c Subject.cpp	

Radius.o: Radius.h
	$(CC) $(CXXFLAGS) -c Radius.cpp

clean:
	rm -f core $(PROG) $(OBJS)