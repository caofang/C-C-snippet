# 


PROG = shop
CC = g++
OBJS = main.o Shop.o DummyProduct.o Subject.o 

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

main.o:
	$(CC) -c main.cpp

Shop.o: Shop.h
	$(CC) -c Shop.cpp

Subject.o: Subject.h
	$(CC) -c Subject.cpp

DummyProduct.o: DummyProduct.h
	$(CC) -c DummyProduct.cpp

clean:
	rm -f core $(PROG) $(OBJS)