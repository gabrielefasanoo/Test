#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Personaggio
{
    char *name[10];
    int *lvl;
    int *hp;
    int *armor;
    char *inventario[10];
} PG;

void inserimento_nome(PG *pg)
{
    printf("Inserisci un nome per il tuo personaggio\n");
    scanf("%s", pg->name);
    printf("Il tuo nome e': %s\n", pg->name);
}
int statistiche(PG *pg)
{
    pg->hp = pg->hp + 25;
    pg->armor = pg->armor + 5;

    // aumento della vita e dell'armor in base al livello
    if (*pg->lvl > 1)
    {
        *pg->hp = *pg->hp + (25) * (*pg->lvl);
        *pg->armor = *pg->armor + (5) * (*pg->lvl);
    }
}
int inventario(PG *pg)
{

}

int main()
{
    PG pg;
    *pg.lvl = 1;
    inserimento_nome(&pg);
    statistiche(&pg);
    return 0;
}