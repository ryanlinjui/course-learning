.IGNORE : all clean

all:
	gcc -c mymatch.c -o mymatch.o
	gcc hw0201.c mymatch.o -o hw0201
	gcc hw0202.c -o hw0202
	# gcc -c madoka.c -o madoka.o
	# gcc hw0203.c madoka.o -o hw0203
	gcc hw0204.c -o hw0204
	# gcc -c myvector.c -o myvector.o -lm
	# gcc hw0205.c myvector.o -o hw0205 -lm
	gcc bonus.c -o bonus

clean:
	rm *.o hw0?0? *.zip bonus
	
zip:
	zip -r hw02.zip *.c Makefile *.pdf *.h