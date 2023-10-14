CC=gcc
CFLAGS=-m32 -nostartfiles -Wall -Wextra -g -ggdb3
EXEC=main.out

$(EXEC): minimal.s
	$(CC) $(CFLAGS) -o $@ $^

run:
	make && ./$(EXEC)

debug:
	make && gdb ./$(EXEC)

clean:
	rm -f *.out 
