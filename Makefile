#/* STEGARUS Petre-Florin - 313CB */

build: 
	gcc -o tema3 testfunctions.c tema.c trie.c -Wall -lm -g -std=c99
run:
	./tema3

.PHONY : clean
clean :
	rm -rf tema3