# Makefile for sorting_algorithms
# usage: make [target]

CC=gcc
CFLAGS=-Wall -Wextra

%: %.c
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -f *.out