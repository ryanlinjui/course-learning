.IGNORE : all clean

all:
	gcc fin01.c -o fin01

	gcc -c frac.c -o frac.o
	gcc fin03.c frac.o -o fin03

clean:
	rm *.o fin0?

zip:
	zip -r fin.zip *.c *.h Makefile README.md bonus.txt