.IGNORE : all clean

all:
	gcc -c mymatch.c -o mymatch.o
	gcc hw0201.c mymatch.o -o hw0201
	# gcc hw0202.c -o hw0202

clean:
	rm *.o hw0?0? *.zip bonus
	
zip:
	zip -r hw02.zip *.c Makefile *.pdf *.h