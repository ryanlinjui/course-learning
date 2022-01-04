.IGNORE : all clean

all:
	gcc -c mirror.c -o mirror.o
	gcc hw0601.c mirror.o -o hw0601

	gcc -c ext.c -o ext.o
	gcc hw0602.c ext.o -o hw0602

	gcc hw0603.c -o hw0603

	gcc hw0604.c -o hw0604

	gcc -c mymem.c -o mymem.o
	gcc hw0605.c mymem.o -o hw0605

	gcc bonus.c -o bonus

clean:
	rm *.o hw060? bonus 

zip:
	zip -r hw06.zip hw060?.c *.h README.md Makefile bonus.pdf