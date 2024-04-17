.IGNORE : all clean

all:
	gcc -c matrix.c -o matrix.o -lm
	gcc main.c matrix.o -o main -lm

clean:
	rm *.o main