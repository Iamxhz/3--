main: test.o mycmd.o
	gcc test.o mycmd.o -o main
test.o: test.c
	gcc -c test.c -o test.o
mycmd.o: mycmd.c
	gcc -c mycmd.c -o mycmd.o
clean:
	rm -f *.o main
