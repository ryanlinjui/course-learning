.IGNORE : all clean

all:
	gcc fin01.c -o fin01

	gcc -c go.c -o go.o
	gcc fin02.c go.o -o fin02

	gcc -c frac.c -o frac.o
	gcc fin03.c frac.o -o fin03

	gcc -c mem.c -o mem.o
	gcc fin04.c mem.o -o fin04

clean:
	rm *.o fin0?

zip:
	zip -r fin.zip *