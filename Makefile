test: test.o parser.o
	gcc test.o parser.o -o test

test.o: test.c
	gcc -c test.c -o test.o

parser.o: parser.c parser.h
	gcc -c parser.c -o parser.o