CC=g++

CFLAGS=-std=c++2a -Wall -O3 -o 

all:
	$(CC) $(CFLAGS) taefl_cli main.cpp taefl.cpp

clean:
	rm -rf *.o taefl_cli
