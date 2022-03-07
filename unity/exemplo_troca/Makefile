all: test-main

test-main: test-main.o troca.o unity.o
	gcc -o test-main test-main.o troca.o unity.o

test-main.o: test-main.c
	gcc -c test-main.c

troca.o:
	gcc -c troca.c 

unity.o:
	gcc -c unity.c

clean:
	rm *.o test-main
