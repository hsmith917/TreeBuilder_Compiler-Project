# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

all: test scanner

scanner: lex.yy.c
	$(CC) $(CFLAGS) -o $@ $^

test: test.cc
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.c: tree_builder.l
	flex $^


clean:
	rm -f test lex.yy.c scanner

.PHONY: all clean
