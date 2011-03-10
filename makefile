CC=g++

.SUFFIXES: .cc .o

.cc.o:
	$(CC) -g -c $*.cc

all: qm

qm: main.o minterm.o
	$(CC) -o qm main.o minterm.o

clean : 
	rm -f *.o qm

main.o: main.cpp
minterm.o: minterm.cc
