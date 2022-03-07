all: test

test: test.o soma.o
	gcc -o test test.o soma.o

test.o: test.c
	gcc -c test.c

soma.o:
	gcc -c soma.c 

clean:
	rm *.o test
