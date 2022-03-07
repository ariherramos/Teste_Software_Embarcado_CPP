all: test-main

test-main: test-main.o conjunto.o unity.o
	gcc -o test-main test-main.o conjunto.o unity.o

test-main.o: test-main.c
	gcc -c test-main.c

conjunto.o:
	gcc -c conjunto.c 

unity.o:
	gcc -c unity.c

clean:
	rm *.o test-main
