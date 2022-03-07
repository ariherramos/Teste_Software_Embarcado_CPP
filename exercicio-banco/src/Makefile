all: main

main: main.o banco.o deposit.o
	gcc -o main main.o banco.o deposit.o

main.o: main.c
	gcc -c main.c

banco.o:
	gcc -c banco.c 

deposit.o:
	gcc -c deposit.c 

clean:
	rm *.o main
