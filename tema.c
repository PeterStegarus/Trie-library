/* STEGARUS Petre-Florin - 313CB */

#include "tema.h"

int LexicoPos(char c)
{
    return strchr(alphabet, c) - alphabet;
}

Book *InitBook(char *title, char *author, int rating, int pages)
{
    Book *b = malloc(sizeof(Book));
    strcpy(b->title, title);
    strcpy(b->author, author);
    b->rating = rating;
    b->pages = pages;
    return b;
}

void AddT1(Tree t1, Book *b)
{
    int i = 0;
    while (b->title[i] != '\0') {
        if (t1->cv[LexicoPos(b->title[i])] == NULL)
            t1->cv[LexicoPos(b->title[i])] = InitNode(NULL);
        t1 = t1->cv[LexicoPos(b->title[i])];
        i++;
    }
    t1->info = b;
}

void AddT2(Tree t2, Book *b)
{
    int i = 0;
    while (b->author[i] != '\0') {
        if (t2->cv[LexicoPos(b->author[i])] == NULL)
            t2->cv[LexicoPos(b->author[i])] = InitNode(NULL);
        t2 = t2->cv[LexicoPos(b->author[i])];
        i++;
    }
    if (t2->info == NULL)
        t2->info = InitNode(NULL);
    AddT1(t2->info, b);
}

void AddBook(Tree t1, Tree t2, char *buffer)
{
    char *title = strtok(buffer, ":"), *author = strtok(NULL, ":");
    int rating, pages;
    buffer = strtok(NULL, "");
    sscanf(buffer, "%d:%d", &rating, &pages);
    Book *b = InitBook(title, author, rating, pages);
    AddT1(t1, b);
    AddT2(t2, b);
}

void SearchBook(Tree t1, char *title)
{
    printf("[%s]\n", title);
    int i = 0;
    while (title[i] != '\0') {
        if (t1->cv[LexicoPos(title[i])] == NULL)
            t1->cv[LexicoPos(title[i])] = InitNode(NULL);
        t1 = t1->cv[LexicoPos(title[i])];
        i++;
    }
}

int main(int argc, char *argv[])
{
    Tree t1 = malloc(sizeof(Node));
    Tree t2 = malloc(sizeof(Node));

	int cursor;
	FILE *fin = fopen(argv[1], "r");
	freopen(argv[2], "w", stdout);
	char buffer[N_LENGTH * 3], command[N_LENGTH];

	while (fgets(buffer, sizeof(buffer), fin)) {
		//in cazul in care sunt linii libere gen "\n" in input:
		if (sscanf(buffer, "%s %n", command, &cursor) < 1)
			continue;
        if (!strcmp(command, "add_book")) {
            AddBook(t1, t2, buffer + cursor);
        } else if (!strcmp(command, "search_book")) {
            char *title = buffer + cursor;
            if (title[strlen(title) - 1] == '\n')
                title[strlen(title) - 1] = '\0';
            SearchBook(t1, buffer + cursor);
        }
	}
	fclose(fin);
    // PrintAll(t1, t2);
	return 0;
}