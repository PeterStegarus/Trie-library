/* STEGARUS Petre-Florin - 313CB */

#include "trie.h"

Tree InitNode(void *info)
{
    Tree t = malloc(sizeof(Node));
    t->info = info;
    for (int i = 0; i < 68; ++i)
        t->cv[i] = NULL;
    return t;
}