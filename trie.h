/* STEGARUS Petre-Florin - 313CB */

#ifndef tTrie
#define tTrie
#include <string.h>
#include <stdlib.h>

typedef struct snode
{
    void *info;
    struct snode *cv[68];    //children array
} Node, *Tree;

typedef void (*TF)(void *);

extern const char alphabet[];
int LexicoPos(char c);
Tree InitNode(void *info);
int IsEnd(Tree T);
int CheckFreeEnd(Tree *T);
Tree TrieGet(Tree T, char *key, int addFlag);
int TrieInsert(Tree T, char *key, void *info, TF fr);
#endif