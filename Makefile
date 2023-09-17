CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

all: PhotoMagic test

PhotoMagic: PhotoMagic.o FibLFSR.o
	$(CC) $(CFLAGS) -o PhotoMagic PhotoMagic.o FibLFSR.o $(LIB)
test: test.o FibLFSR.o
	$(CC) $(CFLAGS) -o test test.o FibLFSR.o $(LIB)
PhotoMagic.o: PhotoMagic.cpp FibLFSR.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -c PhotoMagic.cpp
FibLFSR.o: FibLFSR.cpp 
	$(CC) $(CFLAGS) -c FibLFSR.cpp
test.o: test.cpp FibLFSR.hpp FibLFSR.cpp
	$(CC) $(CFLAGS) -c test.cpp
clean:
	rm *.o PhotoMagic test
