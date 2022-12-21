#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Personaggio
{
    char name[10];
    int lvl;
    int hp;
    int armor;
} PG;

void inserimento_nome(PG *pg)
{
    printf("Inserisci un nome per il tuo personaggio\n");
    scanf("%s", pg->name);
    printf("Il tuo nome e': %s\n", pg->name);
}

int main()
{
    PG pg;
    inserimento_nome(&pg);
    return 0;
}