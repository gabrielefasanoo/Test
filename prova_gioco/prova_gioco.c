#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SIZE_INV 21
#define SIZE_EQUIP 5

typedef struct Personaggio
{
    char *name[10];
    int *lvl;
    int *hp;
    int *armor;
} ST;

typedef struct Oggetto
{
    char *nome[20];
    int *Durability;
    const char *Rarity;
    int *Damage;
    char *Descrizione[500];
    char *Tipo;

} O;

void SetColor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}
void print_decorate_sentence(char sentence[1000])
{
    int length; // Create a variable to hold the length of the sentence

    // Calculate the length of the sentence
    length = strlen(sentence);

    // Remove the newline character from the end of the sentence
    sentence[strlen(sentence) - 1] = '\0';

    // Calculate the length of the sentence
    length = strlen(sentence);

    // Print the top border of asterisks
    for (int i = 0; i < length + 6; i++)
    {
        printf("=");
    }
    printf("\n");

    // Print the left border of asterisks with a space in the middle
    for (int i = 0; i < 2; i++)
    {
        printf("|  ");
        for (int j = 0; j < length; j++)
        {
            printf(" ");
        }
        printf("  |\n");
    }

    // Print the left border of asterisks and the sentence
    printf("|  ");
    printf("%s", sentence); // Print the sentence entered by the user
    printf("  |\n");

    // Print the left border of asterisks with a space in the middle
    for (int i = 0; i < 2; i++)
    {
        printf("|  ");
        for (int j = 0; j < length; j++)
        {
            printf(" ");
        }
        printf("  |\n");
    }

    // Print the bottom border of asterisks
    for (int i = 0; i < length + 6; i++)
    {
        printf("=");
    }
    printf("\n\n");
}
int inserimento_nome(ST *pg)
{
    SetColor(9); // blu
    char sentence_nome[1000] = ("Inserisci un nome per il tuo personaggio\n");
    print_decorate_sentence(sentence_nome);
    SetColor(7); // bianco
    scanf("%s", pg->name);
    SetColor(9); // blu
    printf("Il tuo nome sara': %s, lo confermi? (Y)Si o (N))No\n", pg->name);
    char conferma_nome;
    SetColor(7); // bianco
    scanf("%s", &conferma_nome);
    if (conferma_nome == 'Y' || conferma_nome == 'y')
    {
        
    }
    if (conferma_nome == 'N' || conferma_nome == 'n')
    {
        inserimento_nome(pg);
    }
    else {
        SetColor(4); //rosso
        printf("Risposta non valida, riprova\n");
        inserimento_nome(pg);
    }
}
int statistiche(ST *pg)
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
int inv_zaino_iniziale(ST *pg, O *inventario)
{
    inventario[0].nome[20] = "Spada di seconda mano";
    inventario[0].Descrizione[500] = "Spada di ferro scadente, sicuramente si rompera' presto...";
    inventario[0].Tipo[0];
    inventario[0].Rarity[0];
    *inventario[0].Damage = 10;
    *inventario[0].Durability = 20;
    
    inventario[1].nome[20] = "Scudo di fortuna";
    inventario[1].Descrizione[500] = "Scudo di legno scadente, sicuramente si rompera' presto...";
    inventario[1].Tipo[0];
    inventario[1].Rarity[0];
    *inventario[1].Damage = 0;
    *inventario[1].Durability = 20;
    
    inventario[2].nome[20] = "Pozione di guarigione";
    inventario[2].Descrizione[500] = "Pozione di guarigione, ristabilisce 10 punti vita";
    inventario[2].Tipo[0];
    inventario[2].Rarity[0];
    *inventario[2].Damage = 0;
    *inventario[2].Durability = 1;
}

int main()
{
    ST pg; // dichiarazione del personaggio
    *pg.lvl = 1; 
    const char *Rarity[]={"Comune", "Raro", "Epico", "Leggendario"}; // array di rarita'
    const char *Tipo[]={"Arma", "Armatura", "Guarigione", "Buff", "Debuff", "Veleno"}; // array di tipi
    O inventario[SIZE_INV]; // array di oggetti
    O equipaggiamento[SIZE_EQUIP]; // array di oggetti equipaggiati
    inserimento_nome(&pg); // funzione per l'inserimento del nome del personaggio
    statistiche(&pg); // funzione per l'inserimento delle statistiche del personaggio
    // funzione per l'inserimento degli oggetti nell'inventario
    inv_zaino_iniziale(&pg, inventario);
    SetColor(2); //verde
    printf("programma riuscito..."); // messaggio di conferma
    return 0;
}