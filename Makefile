CC = gcc
CFLAGS = -Wall -g

all: memory.o chunk.o main.o debug.o value.o
	$(CC) $(CFLAGS) -o clox memory.o chunk.o  main.o debug.o value.o

memory.o : memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

chunk.o : chunk.c chunk.h memory.h value.h
	$(CC) $(CFLAGS) -c chunk.c

debug.o : debug.c debug.h value.h
	$(CC) $(CFLAGS) -c debug.c

value.o : value.c value.h memory.h
	$(CC) $(CFLAGS) -c value.c

main.o : main.c common.h chunk.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o clox

