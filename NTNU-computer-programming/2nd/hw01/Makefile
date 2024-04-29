.IGNORE : all clean

all:
	gcc hw0101.c -o hw0101
	gcc hw0102.c -o hw0102
	gcc -c mystring.c -o mystring.o -lm
	gcc hw0103.c mystring.o -o hw0103 -lm
	gcc hw0104.c mystring.o -o hw0104 -lm
	gcc -c mysplit.c -o mysplit.o
	gcc hw0105.c mysplit.o -o hw0105
	gcc bonus.c -o bonus

clean:
	rm *.o hw010? *.zip bonus
	
zip:
	zip -r hw01.zip *.c Makefile *.pdf *.h