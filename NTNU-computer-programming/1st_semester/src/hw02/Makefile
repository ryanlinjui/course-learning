.IGNORE : all clean

all:
	gcc hw0201.c -o hw0201
	gcc hw0202.c -o hw0202
	gcc hw0203.c -o hw0203
	gcc hw0204.c -o hw0204
	gcc hw0205.c -o hw0205
	gcc bonus.c -o bonus

clean:
	rm *.o hw020? bonus *.zip
	
zip:
	zip -r hw02.zip hw020?.c bonus.c Makefile README.md