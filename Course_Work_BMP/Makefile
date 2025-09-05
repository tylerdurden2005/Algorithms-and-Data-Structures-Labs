all: main clean
main: main.o consol.o BmpRead.o BmpChange.o BmpDraw.o
	gcc main.o consol.o BmpRead.o BmpChange.o BmpDraw.o -o cw
main.o: main.c consol.h BmpRead.h BmpChange.h BmpDraw.h
	gcc -c main.c
consol.o: consol.c consol.h BmpRead.h
	gcc -c consol.c 
BmpRead.o: BmpRead.c BmpRead.h
	gcc -c BmpRead.c
BmpChange.o: BmpChange.c BmpChange.h BmpRead.h
	gcc -c BmpChange.c
BmpDraw.o: BmpDraw.c BmpDraw.h  BmpRead.h
	gcc -c BmpDraw.c
clean: 
	rm -rf *.o 
