/* STEGARUS Petre-Florin - 313CB */

#include <string.h>
#include <stdlib.h>

typedef struct snode
{
    void *info;
    struct snode *cv[68];    //children array
} Node, *Tree;

Tree InitNode(void *info);