CC = gcc
CFLAGS = -Wall -g
all: graph
graph: main.c graph.h graph.c
	$(CC) $(CFLAGS) main.c graph.c graph.h -o graph

clean:
	rm -f *.o graph