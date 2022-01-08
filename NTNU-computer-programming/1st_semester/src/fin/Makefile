.IGNORE : all clean

all:
	gcc fin01.c -o fin01

	gcc -c go.c -o go.o
	gcc fin02.c go.o -o fin02

	gcc -c frac.c -o frac.o
	gcc fin03.c frac.o -o fin03

clean:
	rm *.o fin0?

zip:
	zip -r fin.zip *.c *.h Makefile README.md bonus.txt