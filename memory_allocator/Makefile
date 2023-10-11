CC=gcc
CFLAGS=-Wall -Wextra -ggdb
EXEC=main.out

$(EXEC): my_malloc.c main.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	make && ./$(EXEC)

clean:
	rm -f *.out 