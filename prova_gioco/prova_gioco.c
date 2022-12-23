#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <math.h>
#define SIZE_INV 10
#define SIZE_EQUIP 6
#define SIZE_NOME 10
#define SIZE_NOME_OGGETTO 50
#define SIZE_DESCRIZIONE 500
#define SIZE_SENTENCE 1000

typedef struct Personaggio
{
    char name[SIZE_NOME];
    int lvl;
    int hp;
    int armor;
} ST;

typedef struct Oggetto
{
    char nome[SIZE_NOME_OGGETTO];
    char Descrizione[SIZE_DESCRIZIONE];
    char *Tipo;
    const char *Rarity;
    int Value;
    int Durability;
    int Damage;

} O;

void SetColor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}
void print_decorate_choices(char sentence[SIZE_SENTENCE])
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
void print_decorate_sentence(char sentence[SIZE_SENTENCE])
{
    int Length;
    int count = 0;
    for (int i = 0; i < SIZE_SENTENCE; i++)
    {
        if (sentence[i] == '\n')
        {
            count++;
            Length = i;
        }
        if (sentence[i] == '\0')
        {
            Length = i - count;
            break;
        }
    }
    int sentence_length = strlen(sentence);
    int num_middle_chars = ceil(((double)sentence_length - 2) / 4);
    printf("+");
    int i;
    for (i = 0; i < num_middle_chars; i++)
    {
        if (i == 0)
        {
            printf("---");
        }
        else
        {
            printf("~---");
        }
    }
    printf("+\n");
    // make a loop to print the sentence
    for (int i = 0; i < sentence_length; i++)
    {
        printf("%c", sentence[i]);
    }
    // print the bottom border
    printf("+");
    for (i = 0; i < num_middle_chars; i++)
    {
        if (i == 0)
        {
            printf("---");
        }
        else
        {
            printf("~---");
        }
    }
    printf("+\n");
}
void inserimento_nome(ST *pg)
{
    SetColor(9); // blu
    char sentence_nome[SIZE_SENTENCE] = ("Inserisci un nome per il tuo personaggio\n");
    print_decorate_sentence(sentence_nome);
    SetColor(7); // bianco
    scanf("%s", pg->name);
    SetColor(9); // blu
    if (strlen(pg->name) > SIZE_NOME)
    {
        SetColor(4); // rosso
        printf("nome troppo lungo\n\n");
        inserimento_nome(pg);
    }
    if (strlen(pg->name) <= 3)
    {
        SetColor(4); // rosso
        printf("nome non valido\n\n");
        inserimento_nome(pg);
    }
    if (strlen(pg->name) <= SIZE_NOME && strlen(pg->name) > 3)
    {
        SetColor(2); // verde
        printf("nome inserito correttamente\n\n");
    }
    SetColor(9); // blu
    char sentence_conferma[SIZE_SENTENCE] = ("Lo confermi? (Y)Si o (N))No\n");
    print_decorate_choices(sentence_conferma);
    char conferma_nome;
    SetColor(7); // bianco
    scanf("%s", &conferma_nome);
    switch (conferma_nome)
    {
    case 'Y':
        SetColor(2); // verde
        printf("Nome confermato\n");
        break;
    case 'N':
        inserimento_nome(pg);
        break;
    case 'y':
        SetColor(2); // verde
        printf("Nome confermato\n");
        break;
    case 'n':
        inserimento_nome(pg);
        break;
    default:
        SetColor(4); // rosso
        printf("Inserisci un opzione valida\n");
        inserimento_nome(pg);
        break;
    }
}
int statistiche_iniziali(ST *pg)
{
    pg->hp = pg->hp + 25;
    pg->armor = pg->armor + 5;
}
int inv_zaino_iniziale(O *inventario)
{
    int i;
    for (i = 0; i < SIZE_INV; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(inventario[i].nome, "Pozione di guarigione");
            strcpy(inventario[i].Descrizione, "Pozione che guarisce 10 punti vita");
            inventario[i].Tipo, "Guarigione";
            inventario[i].Rarity = "Comune";
            inventario[i].Value = 10;
            inventario[i].Durability = 1;
            inventario[i].Damage = 0;
            break;
        default:
            strcpy(inventario[i].nome, "vuoto");
            strcpy(inventario[i].Descrizione, "");
            inventario[i].Tipo = "";
            inventario[i].Rarity = "";
            inventario[i].Value = 0;
            inventario[i].Durability = 0;
            inventario[i].Damage = 0;
            break;
        }
    }
}
int equip_iniziale(ST *pg, O *equipaggiamento)
{
    int i;
    for (i = 0; i < SIZE_EQUIP; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(equipaggiamento[i].nome, "Spada");
            strcpy(equipaggiamento[i].Descrizione, "Spada di legno di seconda mano, si rompe facilmente...");
            equipaggiamento[i].Tipo = "Arma";
            equipaggiamento[i].Rarity = "Comune";
            equipaggiamento[i].Value = 5;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 10;
            break;
        case 1:
            strcpy(equipaggiamento[i].nome, "Scudo di legno");
            strcpy(equipaggiamento[i].Descrizione, "Scudo di legno di seconda mano, si rompe facilmente...");
            equipaggiamento[i].Tipo = "Armatura";
            equipaggiamento[i].Rarity = "Comune";
            equipaggiamento[i].Value = 2;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 0;
            break;
        case 2:
            strcpy(equipaggiamento[i].nome, "Elmo di cuoio");
            strcpy(equipaggiamento[i].Descrizione, "Elmo di cuoio di semplice fattura, fa il suo dovere...");
            equipaggiamento[i].Tipo = "Armatura";
            equipaggiamento[i].Rarity = "Comune";
            equipaggiamento[i].Value = 5;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 0;
            break;
        case 3:
            strcpy(equipaggiamento[i].nome, "Corazza di cuoio");
            strcpy(equipaggiamento[i].Descrizione, "Corazza di cuoio di semplice fattura, fa il suo dovere...");
            equipaggiamento[i].Tipo = "Armatura";
            equipaggiamento[i].Rarity = 0;
            equipaggiamento[i].Value = 5;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 0;
            break;
        case 4:
            strcpy(equipaggiamento[i].nome, "Pantaloni di cuoio");
            strcpy(equipaggiamento[i].Descrizione, "Pantaloni di cuoio di semplice fattura, fa il suo dovere...");
            equipaggiamento[i].Tipo = "Armatura";
            equipaggiamento[i].Rarity = "Comune";
            equipaggiamento[i].Value = 5;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 0;
            break;
        case 5:
            strcpy(equipaggiamento[i].nome, "Stivali di cuoio");
            strcpy(equipaggiamento[i].Descrizione, "Stivali di cuoio di semplice fattura, fa il suo dovere...");
            equipaggiamento[i].Tipo = "Armatura";
            equipaggiamento[i].Rarity = "Comune";
            equipaggiamento[i].Value = 5;
            equipaggiamento[i].Durability = 10;
            equipaggiamento[i].Damage = 0;
            break;
        default:
            strcpy(equipaggiamento[i].nome, "vuoto");
            strcpy(equipaggiamento[i].Descrizione, "Descrizione non disponibile");
            equipaggiamento[i].Tipo = "";
            equipaggiamento[i].Rarity = "";
            equipaggiamento[i].Value = 0;
            equipaggiamento[i].Durability = 0;
            equipaggiamento[i].Damage = 0;
            break;
        }
    }
}
int zaino(ST *pg, O *inventario)
{
    int cont = 0;
    SetColor(5); // viola
    for (int i = 0; i < SIZE_INV; i++)
    {
        if (strcmp(inventario[i].nome, "vuoto") == 0)
        {
            cont = cont + 1;
            break;
        }
    }
    printf("+---~---~---~ZAINO~---~---~---+\n");
    // stampare la lista degli oggetti presenti nel zaino
    int i;
    for (i = 0; i < SIZE_INV; i++)
    {
        // stampa nome oggetto
        printf("> %s\n", inventario[i].nome);
    }
    printf("+---~---~---~[ %d ]~---~---~---+\n", cont);
}

int main()
{
    ST pg;
    inserimento_nome(&pg);
    statistiche_iniziali(&pg);
    const char *Rarity[] = {"Comune", "Raro", "Epico", "Leggendario"};
    const char *Tipo[] = {"Arma", "Armatura", "Guarigione", "Buff", "Debuff", "Veleno"};
    O inventario[SIZE_INV];
    O equipaggiamento[SIZE_EQUIP];
    inv_zaino_iniziale(inventario);
    equip_iniziale(&pg, equipaggiamento);
    zaino(&pg, inventario);
    SetColor(2); // verde
    printf("programma riuscito...");
    return 0;
}