CC=gcc
CFLAGS=-I .

testlist: testlist.o list.o
	$(CC) -o testlist testlist.o list.o -I .
