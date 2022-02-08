.IGNORE : all clean

all:
	gcc -c poker.c -o poker.o
	gcc poker.o hw0501.c -o hw0501

	gcc -c data.c -o data.o -lm
	gcc data.o hw0502.c -o hw0502 -lm

	gcc -c polynomial.c -o polynomial.o 
	gcc polynomial.o hw0503.c -o hw0503

	gcc -c bitboard.c -o bitboard.o
	gcc -c banqi.c -o banqi.o
	gcc banqi.o bitboard.o hw0504.c -o hw0504

	gcc bonus.c -o bonus

clean:
	rm *.o hw050? bonus

zip:
	zip -r hw05.zip *.c *.h README.md Makefile *.pdf