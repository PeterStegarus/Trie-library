#include "testfunctions.h"
char alphabet2[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
void PrintTreeBooks(Tree t1, int k)
{
    printf("\tsttBOOK: [%s] | [%c]{\n", ((Book *)t1->info)->title, alphabet2[k]);
    for (int i = 0; i < 68; ++i)
        if (t1->cv[i] != NULL) {
            printf("\t[%c]", alphabet2[i]);
            PrintTreeBooks(t1->cv[i], i);
        }
    printf("\t\tendBOOK: [%s] | [%c]}\n", ((Book *)t1->info)->title, alphabet2[k]);
}

void PrintTreeAuthors(Tree t1, int k)
{
    printf("\tsttAU: [%c]{\n", alphabet2[k]);
    if (t1->info != NULL) {
        printf("aubooks:\n");
        PrintTreeBooks(t1->info, 0);
        printf("endaubooks\n");
    }
    for (int i = 0; i < 68; ++i)
        if (t1->cv[i] != NULL) {
            printf("[%c]", alphabet2[i]);
            PrintTreeAuthors(t1->cv[i], i);
        }
    printf("\tendAU: [%c]}\n", alphabet2[k]);
}

void PrintAll(Tree t1, Tree t2)
{
    printf("t1:\n");
    PrintTreeBooks(t1, 0);
    printf("\n\nt2:\n");
    PrintTreeAuthors(t2, 0);

}
