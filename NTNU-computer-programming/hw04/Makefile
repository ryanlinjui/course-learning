all:
	@gcc -c k_function.c 
	@gcc hw0401.c k_function.o -o hw0401

	@gcc -c -lm hanoi.c
	@gcc hw0402-1.c hanoi.o -lm -o hw0402-1
	@gcc hw0402-2.c hanoi.o -lm -o hw0402-2

	@gcc -c -lm triangle.c
	@gcc hw0403.c triangle.o -lm -o hw0403

	@gcc -c euqivalent_r.c
	@gcc hw0404.c euqivalent_r.o -o hw0404
	
	@gcc bonus.c -o bonus

	@echo "Compile completed!!"

zip:
	@zip hw04 *
	@echo "Zip completed!!"

clean:
	@rm *.o hw040? hw0402-? *.zip
	@echo "Clean completed!!"