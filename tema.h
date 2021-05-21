/* STEGARUS Petre-Florin - 313CB */

#include <stdio.h>
#include "trie.h"
#include "book.h"

#define N_LENGTH 55

void DeleteBookFA(Tree *t2, Book *b);
int DeleteBookAux(Tree *t1, Tree *t2, char *title, int nested);