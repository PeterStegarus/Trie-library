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

//adauga o carte in arborele de carti
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

//adauga o carte in arborele unui autor
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

//adauga o carte in cei doi arbori
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

//afiseaza cartile din subarborele t1
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

//afiseaza cartile al caror titlu incepe cu prefixul prefix
void AutocompleteBook(Tree t1, char *prefix, int c)
{
    prefix[strlen(prefix) - 1] = '\0';
    int i = 0;
    while (prefix[i] != '\0') {
        t1 = t1->cv[LexicoPos(prefix[i])];
        if (t1 == NULL) {
            printf("Nicio carte gasita.\n");
            return;
        }
        i++;
    }
    int ct = c;
    AutocompleteBookAux(t1, &ct);
}

//cauta o carte dupa titlu sau dupa un prefix al titlului
void SearchBook(Tree t1, char *title)
{
    if (title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
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
        printf("Informatii recomandare: %s, %s, %d, %d\n",\
        b->title,b->author, b->rating, b->pages);
    else
        printf("Cartea %s nu exista in recomandarile tale.\n", title);
}

//afiseaza primii 3 autori din subarborele t2
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
        if (t2->cv[i] != NULL) {
            AutocompleteListAuthorAux(t2->cv[i], ct, aut);
        }
    }
}

//afiseaza numele autorilor care incep cu prefix~
void AutocompleteListAuthor(Tree t2, char *prefix)
{
    prefix[strlen(prefix) - 1] = '\0';
    int i = 0;
    while (prefix[i] != '\0') {
        t2 = t2->cv[LexicoPos(prefix[i])];
        if (t2 == NULL) {
            printf("Niciun autor gasit.\n");
            return;
        }
        i++;
    }
    int ct = 0;
    AutocompleteListAuthorAux(t2, &ct, prefix);
}

//afiseaza cartile unui autor sau numele autorilor care incep cu un prefix~
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
            printf("Autorul %s nu face parte din recomandarile tale.\n",\
            author);
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

//afiseaza carti din arborele autorului al caror titlu incepe cu prefixul title
void AutocompleteSBA(Tree t2, char *author, char *title)
{
    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Autorul %s nu face parte din recomandarile tale.\n",\
            author);
            return;
        }
        i++;
    }
    Tree t1 = t2->info;
    if (t1 != NULL) {
        AutocompleteBook(t1, title, 0);
    }
}

//cauta cartea cu un titlu anume al unui autor anume, dupa titlu sau prefix
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
        AutocompleteSBA(t2, author, title);
        return;
    }

    int i = 0;
    while (author[i] != '\0') {
        t2 = t2->cv[LexicoPos(author[i])];
        if (t2 == NULL) {
            printf("Autorul %s nu face parte din recomandarile tale.\n",\
            author);
            return;
        }
        i++;
    }
    Tree t1 = t2->info;
    if (t1 != NULL)
        SearchBook(t1, title);
    else
        printf("Autorul %s nu face parte din recomandarile tale.\n", author);

}

/*sterge cartea din arborele de carti al autorului si apoi autorul daca nu mai
are carti*/
void DeleteBookFA(Tree *t2, Book *b)
{
    if (b == NULL)
        return;
    Tree t = *t2;
    int i = 0;
    while (b->author[i] != '\0') {
        t = t->cv[LexicoPos(b->author[i])];
        i++;
        if (t == NULL)
            return;
    }
    Tree t1 = t->info;
    if (t1 != NULL) {
        char author[51];
        int isvoid = 1;
        strcpy(author, b->author);
        DeleteBookAux(&t1, t2, b->title, 1);
        if (t1 != NULL)
            for (int i = 0; i < 68; ++i)
                if (t1->cv[i] != NULL) {
                    isvoid = 0;
                    break;
                }
        if (isvoid)
            DeleteBookAux(t2, t2, author, 1);
    }
}

/*parcurg toate nodurile care duc la cartea cu titlul title si le sterg daca
ele conduc doar catre cartea care trebuie stearsa*/
int DeleteBookAux(Tree *t1, Tree *t2, char *title, int nested)
{
    if (*title == '\0') {
        if (!nested) {
            Book *b = (*t1)->info;
            if (b == NULL)
                return -1;
            DeleteBookFA(t2, b);
            free((*t1)->info);
            (*t1)->info = NULL;
        }
        int end = 1;
        for (int i = 0; i < 68; ++i)
            if ((*t1)->cv[i] != NULL) {
                end = 0;
                break;
            }
        if (end) {
            free(*t1);
            *t1 = NULL;
        }
        return end;
    }

    if ((*t1)->cv[LexicoPos(title[0])] == NULL)
        return -1;

    int rez = DeleteBookAux(&((*t1)->cv[LexicoPos(title[0])]),\
    t2, title + 1, nested);
    if (rez == -1)
        return -1;

    if ((*t1)->info == NULL && rez) {
        int end = 1;
        for (int i = 0; i < 68; ++i)
            if ((*t1)->cv[i] != NULL) {
                end = 0;
                break;
            }

        if (end) {
            free(*t1);
            *t1 = NULL;
        }
        return end;
    }
    return 0;
}

//sterg cartea cu titlul title din arborele de carti si din cel al autorului
void DeleteBook(Tree *t1, Tree *t2, char *title)
{
    if (title[strlen(title) - 1] == '\n')
        title[strlen(title) - 1] = '\0';
    if (DeleteBookAux(t1, t2, title, 0) == -1)
        printf("Cartea %s nu exista in recomandarile tale.\n", title);
}

//elibereaza memoria arborelui de carti
void FreeTreeBooks(Tree t1, int subtree)
{
    for (int i = 0; i < 68; ++i)
        if (t1->cv[i] != NULL) {
            FreeTreeBooks(t1->cv[i], subtree);
        }
    if (!subtree) {
        free(t1->info);
        t1->info = NULL;
    }
    free(t1);
    t1 = NULL;
}

//elibereaza memoria arborelui de autori
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

//elibereaza memoria ramasa inca alocata
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
		//in cazul in care sunt linii libere in input:
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
        } else if (!strcmp(command, "delete_book")) {
            DeleteBook(&t1, &t2, buffer + cursor);
        }
	}
	fclose(fin);
    FreeAll(t1, t2);
	return 0;
}