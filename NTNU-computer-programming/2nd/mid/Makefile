.IGNORE : all clean

all:
	gcc -c mystring.c -o mystring.o
	gcc mid01.c mystring.o -o mid01

	gcc mid02.c -o mid02
	
clean:
	rm *.o mid0? *.zip
	
zip:
	zip -r mid.zip *