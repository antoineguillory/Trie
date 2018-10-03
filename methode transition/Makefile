CC= gcc
CFLAGS= -std=c11 -Wall -Wpedantic -Wextra -Werror -Wconversion
PRGS = trie

all: $(PRGS)

trie: trie.o 

trie.o: trie.c trie.h

clean: 
	rm *.o*~
