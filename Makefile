CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

all: memory.o chunk.o main.o debug.o value.o vm.o
	$(CC) $(CFLAGS) -o clox memory.o chunk.o  main.o debug.o value.o vm.o

memory.o : memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

chunk.o : chunk.c chunk.h memory.h value.h
	$(CC) $(CFLAGS) -c chunk.c

debug.o : debug.c debug.h value.h
	$(CC) $(CFLAGS) -c debug.c

value.o : value.c value.h memory.h
	$(CC) $(CFLAGS) -c value.c

vm.o : common.h vm.h
	$(CC) $(CFLAGS) -c vm.c

main.o : main.c common.h chunk.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o clox

