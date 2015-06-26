bfi: bf.o
	gcc -o bfi bf.o
bf.o:
	gcc -c bf.c
clear:
	rm -rf bfi bf.o
