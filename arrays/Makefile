CC=gcc
CFLAGS=-O0 -Wall -Wextra -g -ggdb3
EXEC=main.out
stack=StackArray.c

$(EXEC): $(stack) main.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	make && ./$(EXEC)

debug:
	make && gdb ./$(EXEC)

valgrind:
	make && valgrind --track-origins=yes --leak-check=full ./$(EXEC)

clean:
	rm -f *.out 