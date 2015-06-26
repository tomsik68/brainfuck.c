bfi: bf.o
	gcc -o bfi bf.o
bf.o:
	gcc -c bf.c
clean:
	rm -rf bfi bf.o
