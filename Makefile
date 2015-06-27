CFLAGS = -Wall -ansi
bfi: bf.o configuration.o execution.o loader.o
	gcc $(CFLAGS) -o bfi bf.o configuration.o execution.o loader.o
bf.o: bf.c
	gcc $(CFLAGS) -c bf.c
configuration.o: configuration.c configuration.h
	gcc $(CFLAGS) -c configuration.c
execution.o: configuration.o execution.c execution.h
	gcc $(CFLAGS) -c execution.c
loader.o: execution.o configuration.o loader.c loader.h
	gcc $(CFLAGS) -c loader.c
clean:
	rm -rf bfi bf.o configuration.o execution.o loader.o
