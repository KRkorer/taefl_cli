CC=g++

CFLAGS=-std=c++17 -Wall

all:
	$(CC) main.cpp taefl.cpp  -o taefl_cli

clean:
	rm -rf *.o taefl_cli
