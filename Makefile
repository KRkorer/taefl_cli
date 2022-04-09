CC=g++

CFLAGS=-std=c++2a -Wall -O3

all: taefl_cli

taefl_cli: main.o taefl.o taefl.h
	$(CC) $(CFLAGS) -o taefl_cli main.o taefl.o

taefl.o: taefl.h
	$(CC) $(CFLAGS) -c -o taefl.o taefl.cpp

main.o: taefl.h
	$(CC) $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -rf *.o taefl_cli
