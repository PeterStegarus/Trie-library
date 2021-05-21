/* STEGARUS Petre-Florin - 313CB */

#include "trie.h"

const char alphabet[]  =\
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";

//obtine pozitia din alfabetul primit in cerinta
int LexicoPos(char c)
{
    return strchr(alphabet, c) - alphabet;
}

//initializeaza un nod
Tree InitNode(void *info)
{
    Tree t = malloc(sizeof(Node));
    t->info = info;
    for (int i = 0; i < 68; ++i)
        t->cv[i] = NULL;
    return t;
}

//verifica daca nu are copii
int IsEnd(Tree T)
{
    int end = 1;
        for (int i = 0; i < 68; ++i)
            if ((T)->cv[i] != NULL) {
                end = 0;
                break;
            }
    return end;
}

//
int CheckFreeEnd(Tree *T)
{
    int end = IsEnd(*T);
    if (end) {
        free(*T);
        *T = NULL;
    }
    return end;
}

//obtine nodul parcurgand cheia. addFlag daca se vrea crearea drumului
//spre nodul respectiv daca acesta nu exista.
Tree TrieGet(Tree T, char *key, int addFlag)
{
    int i = 0;
    while (key[i] != '\0') {
        if (T->cv[LexicoPos(key[i])] == NULL) {
            if (!addFlag)
                return NULL;
            T->cv[LexicoPos(key[i])] = InitNode(NULL);
        }
        T = T->cv[LexicoPos(key[i])];
        i++;
    }

    return T;
}

int TrieInsert(Tree T, char *key, void *info, TF fr)
{
    T = TrieGet(T, key, 1);
    if (T->info != NULL) {
        fr(info);
        info = NULL;
        return 0;
    }
    T->info = info;
    return 1;
}