all: wop

wop: wop.o
	g++ -o wop wop.o

wop.o:
	g++ -c main.c
