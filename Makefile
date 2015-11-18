CC=gcc
CFLAGS=-I .

all: testlist testqueue testpool

testlist: testlist.o list.o
	$(CC) -o testlist testlist.o list.o -I .

testqueue: testqueue.o queue.o
	$(CC) -o testqueue testqueue.o queue.o -I .

testpool: testpool.o pool.o
	$(CC) -o testpool testpool.o pool.o -I .

clean:
	rm -f *.o
	rm testpool testlist testqueue
