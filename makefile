CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -c
LDFLAGS =

all: quantization

quantization: quantization.o parse.o trie.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $<

clean:
	rm quantization *.o
