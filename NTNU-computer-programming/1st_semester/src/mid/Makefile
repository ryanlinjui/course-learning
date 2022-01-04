.IGNORE : all clean
all:
	gcc mid01.c -o mid01 -lm
	gcc mid02.c -o mid02
	gcc mid03.c -o mid03 -lm
	gcc mid04.c -o mid04

clean:
	rm *.o mid0?

zip:
	zip -r mid.zip mid0?.c Makefile README.md bonus.txt