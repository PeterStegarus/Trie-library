#/* STEGARUS Petre-Florin - 313CB */

CC = gcc

CFLAGS = -Wall -Wextra -g -std=c99

SRCS = tema.c trie.c

OBJS = $(SRCS:.c=.o)

MAIN = tema3

.PHONY: clean

all:    $(MAIN)
build:	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)