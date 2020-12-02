CC = gcc
CFLAGS = -Wall

all: memory.o chunk.o main.o
	$(CC) $(CFLAGS) -o clox memory.o chunk.o  main.o

memory.o : memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

chunk.o : chunk.c chunk.h memory.h
	$(CC) $(CFLAGS) -c chunk.c

main.o : main.c common.h chunk.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o clox

