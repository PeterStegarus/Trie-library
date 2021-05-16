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

int AddT1(Tree t1, Book *b)
{
    int i = 0;
    while (b->title[i] != '\0') {
        if (t1->cv[LexicoPos(b->title[i])] == NULL)
            t1->cv[LexicoPos(b->title[i])] = InitNode(NULL);
        t1 = t1->cv[LexicoPos(b->title[i])];
        i++;
    }
    if (t1->info != NULL) {
        free(b);
        b = NULL;
        return 0;
    }
    t1->info = b;
    return 1;
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
    if (AddT1(t1, b))
        AddT2(t2, b);
}

void AutocompleteBookAux(Tree t1, int *ct)
{
    if (*ct >= 3)
        return;
    if (t1->info != NULL) {
        (*ct)++;
        Book *b = t1->info;
        printf("%s\n", b->title);
    }
    for (int i = 0; i < 68; ++i)
        if (t1->cv[i] != NULL) {
            AutocompleteBookAux(t1->cv[i], ct);
        }
}

void AutocompleteBook(Tree t1, char *title, int c)
{
    title[strlen(title) - 1] = '\0';
    int i = 0;
    while (title[i] != '\0') {
        t1 = t1->cv[LexicoPos(title[i])];
        if (t1 == NULL) {
            printf("Nicio carte gasita.\n");
            return;
        }
        i++;
    }
    int ct = c;
    AutocompleteBookAux(t1, &ct);
}

void SearchBook(Tree t1, char *buffer)
{
    char *title = buffer;
    if (title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
    // printf("[%s]\n", title);
    if (title[strlen(title) - 1] == '~') {
        AutocompleteBook(t1, title, 0);
        return;
    }
    int i = 0;
    while (title[i] != '\0') {
        t1 = t1->cv[LexicoPos(title[i])];
        if (t1 == NULL) {
            printf("Cartea %s nu exista in recomandarile tale.\n", title);
            return;
        }
        i++;
    }
    Book *b = t1->info;
    if (b != NULL)
        printf("Informatii recomandare: %s, %s, %d, %d\n", b->title, b->author, b->rating, b->pages);
    else
        printf("Cartea %s nu exista in recomandarile tale.\n", title);
}

void AutocompleteListAuthorAux(Tree t2, int *ct, char *author)
{
    if (*ct >= 3)
        return;
    if (t2->info != NULL) {
        (*ct)++;
        printf("%s\n", author);
    }
    char aut[51];
    strcpy(aut, author);
    strcat(aut, " ");

    for (int i = 0; i < 68; ++i) {
        aut[strlen(aut) - 1] = alphabet[i];
        // printf("[%s]\n", aut);
        if (t2->cv[i] != NULL) {
            AutocompleteListAuthorAux(t2->cv[i], ct, aut);
        }
    }
}

void AutocompleteListAuthor(Tree t2, char *author)
{
    author[strlen(author) - 1] = '\0';
    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Niciun autor gasit.\n");
            return;
        }
        i++;
    }
    int ct = 0;
    AutocompleteListAuthorAux(t2, &ct, author);
}

void ListAuthor(Tree t2, char *buffer)
{
    char *author = buffer;
    if (author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';
    if (author[strlen(author) - 1] == '~') {
        AutocompleteListAuthor(t2, author);
        return;
    }
    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Autorul %s nu face parte din recomandarile tale.\n", author);
            return;
        }
        i++;
    }
    Tree t1 = t2->info;
    if (t1 != NULL) {
        char title[2] = "~";
        AutocompleteBook(t1, title, -100);
    }
    else
        printf("Autorul %s nu face parte din recomandarile tale.\n", author);
}

void AcSBA(Tree t2, char *author, char *title)
{
    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Autorul %s nu face parte din recomandarile tale.\n", author);
            return;
        }
        i++;
    }
    Tree t1 = t2->info;
    if (t1 != NULL) {
        AutocompleteBook(t1, title, 0);
    }
}

void SearchByAuthor(Tree t2, char *buffer)
{
    char *author = strtok(buffer, ":"), *title = strtok(NULL, ":");
    if (author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';
    if (author[strlen(author) - 1] == '~') {
        AutocompleteListAuthor(t2, author);
        return;
    }
    if (title[strlen(title) - 1] == '~') {
        AcSBA(t2, author, title);
        return;
    }

    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Autorul %s nu face parte din recomandarile tale.\n", author);
            return;
        }
        i++;
    }
    Tree t1 = t2->info;
    if (t1 != NULL) {
        SearchBook(t1, title);
    }
    else
        printf("Autorul %s nu face parte din recomandarile tale.\n", author);

}

void FreeTreeBooks(Tree t1, int subtree)
{
    for (int i = 0; i < 68; ++i)
        if (t1->cv[i] != NULL) {
            FreeTreeBooks(t1->cv[i], subtree);
        }
    if (!subtree)
        free(t1->info);
    free(t1);
    t1 = NULL;
}

void FreeTreeAuthors(Tree t2)
{
    for (int i = 0; i < 68; ++i)
        if (t2->cv[i] != NULL) {
            FreeTreeAuthors(t2->cv[i]);
        }
    if (t2->info != NULL)
        FreeTreeBooks(t2->info, 1);
    free(t2);
    t2 = NULL;
}

void FreeAll(Tree t1, Tree t2)
{
    FreeTreeBooks(t1, 0);
    FreeTreeAuthors(t2);
}

int main(int argc, char *argv[])
{
    Tree t1 = InitNode(NULL);
    Tree t2 = InitNode(NULL);

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
            SearchBook(t1, buffer + cursor);
        } else if (!strcmp(command, "list_author")) {
            ListAuthor(t2, buffer + cursor);
        } else if (!strcmp(command, "search_by_author")) {
            SearchByAuthor(t2, buffer + cursor);
        }
	}
	fclose(fin);
    FreeAll(t1, t2);
    // PrintAll(t1, t2);
	return 0;
}