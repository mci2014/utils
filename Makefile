CC=gcc
CFLAGS=-I .

all: testlist testqueue

testlist: testlist.o list.o
	$(CC) -o testlist testlist.o list.o -I .

testqueue: testqueue.o queue.o
	$(CC) -o testqueue testqueue.o queue.o -I .

clean:
	rm -f *.o
