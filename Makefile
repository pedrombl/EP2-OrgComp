FILES = main.o quadrado.o algoritmo.o
CFLAGS = -c -Wall -pedantic -O2 -ansi

#Source

all: $(FILES)
	gcc $(FILES) -o my_program

main.o: main.c
	gcc $(CFLAGS) main.c

quadrado.o: quadrado.c 
	gcc $(CFLAGS) quadrado.c

algoritmo.o: algoritmo.c 
	gcc $(CFLAGS) algoritmo.c

clean:
	rm *.o my_program
