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

typedef struct Oggetto
{
    char nome[SIZE_NOME_OGGETTO];
    char Descrizione[SIZE_DESCRIZIONE];
    char *Tipo;
    const char *Rarity;
    int Value;
    int Durability;
    int Damage;
    int Quantity;
} O;

typedef struct Personaggio
{
    char name[SIZE_NOME];
    int lvl;
    int Vita;
    int Vita_Max;
    int Difesa;
    int Danno;
    int Mana;
    int Mana_Max;
    int Exp;
    int Gold;
    O Arma;
    O Elmo;
    O Corazza;
    O Pantaloni;
    O Stivali;
} ST;

void clear()
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

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

void titolo_inizio()
{
    SetColor(9); // blu
    char sentence_titolo[SIZE_SENTENCE] = ("Benvenuto in Dungeon Crawler\n");
    print_decorate_choices(sentence_titolo);
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

void statistiche_iniziali(ST *pg)
{
    pg->Vita_Max = pg->Vita_Max + 25;
    pg->Difesa = pg->Difesa + 5;
    pg->Mana_Max = pg->Mana_Max + 10;
}

void inv_iniziale(O *inventario)
{
    int i;
    for (i = 0; i < SIZE_INV; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(inventario[i].nome, "Pozione di vita [I]");
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

void equip_iniziale(ST *pg, O *equipaggiamento)
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

void print_zaino(O *inventario)
{
    int cont = 0;
    clear();
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
        printf("> (%d)%s\n", i + 1, inventario[i].nome);
    }
    printf("+---~---~---~[ %d ]~---~---~---+\n\n", cont);
}

void print_equipaggiamento(O *equipaggiamento)
{
    int cont = 0;
    clear();
    SetColor(5); // viola
    for (int i = 0; i < SIZE_EQUIP; i++)
    {
        if (strcmp(equipaggiamento[i].nome, "vuoto") == 0)
        {
            cont = cont + 1;
            break;
        }
    }
    printf("+---~---~---~EQUIPAGGIAMENTO~---~---~---+\n");
    int i;
    for (i = 0; i < SIZE_EQUIP; i++)
    {
        // stampa nome oggetto
        printf("> %s\n", i + 1, equipaggiamento[i].nome);
    }
    printf("+---~---~---~[ %d ]~---~---~---+\n\n", cont);
}

void stato_personaggio(ST *pg)
{
    clear();
    SetColor(5); // viola
    printf("+---~---~STATO PERSONAGGIO~---~---+\n");
    printf("> Nome: %s\n", pg->name);
    printf("> HP: %d\n", pg->Vita);
    printf("> MP: %d\n", pg->Mana);
    printf("> XP: %d\n", pg->Exp);
    printf("+---~---~---~---[§]---~---~---~---+\n\n");
}

void save(ST *pg, O *inventario, O *equipaggiamento)
{
    FILE *fp;
    fp = fopen("save.txt", "w");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    fprintf(fp, "%s", pg->name);
    fprintf(fp, "%d", pg->Vita);
    fprintf(fp, "%d", pg->Mana);
    fprintf(fp, "%d", pg->Exp);
    for (int i = 0; i < SIZE_INV; i++)
    {
        fprintf(fp, "%s", inventario[i].nome);
        fprintf(fp, "%s", inventario[i].Tipo);
        fprintf(fp, "%s", inventario[i].Rarity);
        fprintf(fp, "%d", inventario[i].Value);
        fprintf(fp, "%d", inventario[i].Durability);
        fprintf(fp, "%d", inventario[i].Damage);
    }
    for (int i = 0; i < SIZE_EQUIP; i++)
    {
        fprintf(fp, "%s", equipaggiamento[i].nome);
        fprintf(fp, "%s", equipaggiamento[i].Tipo);
        fprintf(fp, "%s", equipaggiamento[i].Rarity);
        fprintf(fp, "%d", equipaggiamento[i].Value);
        fprintf(fp, "%d", equipaggiamento[i].Durability);
        fprintf(fp, "%d", equipaggiamento[i].Damage);
    }
    fclose(fp);
}

void load(ST *pg, O *inventario, O *equipaggiamento)
{
    FILE *fp;
    fp = fopen("save.txt", "r");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }
    fscanf(fp, "%s", pg->name);
    fscanf(fp, "%d", pg->Vita);
    fscanf(fp, "%d", pg->Mana);
    fscanf(fp, "%d", pg->Exp);
    for (int i = 0; i < SIZE_INV; i++)
    {
        fscanf(fp, "%s", inventario[i].nome);
        fscanf(fp, "%s", inventario[i].Tipo);
        fscanf(fp, "%s", inventario[i].Rarity);
        fscanf(fp, "%d", inventario[i].Value);
        fscanf(fp, "%d", inventario[i].Durability);
        fscanf(fp, "%d", inventario[i].Damage);
    }
    for (int i = 0; i < SIZE_EQUIP; i++)
    {
        fscanf(fp, "%s", equipaggiamento[i].nome);
    }
    fclose(fp);
}

void compra_spade(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~--[SPADE]--~---~---~---+\n");
        printf("> (1) Spada di legno {15 G}\n");
        printf("> (2) Spada di rame {25 G}\n");
        printf("> (3) Spada di ferro {35 G}\n");
        printf("> (4) Spada d'acciaio {45 G}\n");
        printf("> (5) Spada d'argento {55 G}\n");
        printf("> (6) Spada magica[I] {65 G}\n");
        printf("> (7) Spada magica[II] {75 G}\n");
        printf("> (8) Spada magica[III] {85 G}\n");
        printf("> (9) Spada magica[IV] {95 G}\n");
        printf("> (10) Spada magica[V] {105 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 15)
        {
            pg->Gold -= 15;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada di legno");
                    strcpy(inventario[i].Descrizione, "Spada di legno, fa quello che deve fare.");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 8;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada di rame");
                    strcpy(inventario[i].Descrizione, "Spada di rame, non molto potente ma comunque utile");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 18;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada di ferro");
                    strcpy(inventario[i].Descrizione, "Spada di ferro, di buona qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 28;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada d'acciaio");
                    strcpy(inventario[i].Descrizione, "Spada d'acciaio, utilizzata da molti guerrieri");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 38;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada d'argento");
                    strcpy(inventario[i].Descrizione, "Spada d'argento, una delle migliori armi");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 48;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada magica [I]");
                    strcpy(inventario[i].Descrizione, "Spada magica, molto potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 58;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada magica!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada magica [II]");
                    strcpy(inventario[i].Descrizione, "Spada magica, di altissima qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 68;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada magica!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada magica [III]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 78;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada magica!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada magica [IV]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente quasi fra tutte");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 88;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada magica!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 105)
        {
            pg->Gold -= 105;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Spada magica [V]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente fra tutte");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 105;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 98;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada magica!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_asce(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~--[NEGOZIO]--~---~---~---+\n");
        printf("> (1) Ascia di legno {20 G}\n");
        printf("> (2) Ascia di rame {30 G}\n");
        printf("> (3) Ascia di ferro {40 G}\n");
        printf("> (4) Ascia d'acciaio {50 G}\n");
        printf("> (5) Ascia d'argento {60 G}\n");
        printf("> (6) Ascia magica[I] {70 G}\n");
        printf("> (7) Ascia magica[II] {80 G}\n");
        printf("> (8) Ascia magica[III] {90 G}\n");
        printf("> (9) Ascia magica[IV] {100} G}\n");
        printf("> (10) Ascia magica[V] {110 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d G]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 20)
        {
            pg->Gold -= 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia di legno");
                    strcpy(inventario[i].Descrizione, "Ascia di legno");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 12;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la spada di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 30)
        {
            pg->Gold -= 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia di rame");
                    strcpy(inventario[i].Descrizione, "Ascia di rame");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 22;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 40)
        {
            pg->Gold -= 40;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia di ferro");
                    strcpy(inventario[i].Descrizione, "Ascia di ferro");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 40;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 32;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 50)
        {
            pg->Gold -= 50;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia d'acciaio");
                    strcpy(inventario[i].Descrizione, "Ascia d'acciaio");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 50;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 42;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 60)
        {
            pg->Gold -= 60;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia d'argento");
                    strcpy(inventario[i].Descrizione, "Ascia d'argento");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 60;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 52;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
    case 6:
        if (pg->Gold >= 70)
        {
            pg->Gold -= 70;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[I]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[I]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 70;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 62;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia magica[I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 80)
        {
            pg->Gold -= 80;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[II]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[II]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 80;
                    inventario[i].Durability = 200;
                    inventario[i].Damage = 72;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia magica[II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 90)
        {
            pg->Gold -= 90;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[III]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[III]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 90;
                    inventario[i].Durability = 300;
                    inventario[i].Damage = 82;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia magica[III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 100)
        {
            pg->Gold -= 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[IV]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[IV]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 400;
                    inventario[i].Damage = 92;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia magica[IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 110)
        {
            pg->Gold -= 110;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[V]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[V]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 110;
                    inventario[i].Durability = 500;
                    inventario[i].Damage = 102;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'ascia magica[V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_lance(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~-[NEGOZIO]-~---~---~---+\n");
        printf("> (1) Lancia di legno {10 G}\n");
        printf("> (2) Lancia di rame {20 G}\n");
        printf("> (3) Lancia di ferro {30 G}\n");
        printf("> (4) Lancia d'acciaio {40 G}\n");
        printf("> (5) Lancia d'argento {50 G}\n");
        printf("> (6) Lancia magica[I] {60 G}\n");
        printf("> (7) Lancia magica[II] {70 G}\n");
        printf("> (8) Lancia magica[III] {80 G}\n");
        printf("> (9) Lancia magica[IV] {90 G}\n");
        printf("> (10) Lancia magica[V] {100 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d G]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia di legno");
                    strcpy(inventario[i].Descrizione, "Una lancia di legno");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 6;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 20)
        {
            pg->Gold -= 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia di rame");
                    strcpy(inventario[i].Descrizione, "Una lancia di rame");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 16;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 30)
        {
            pg->Gold -= 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia di ferro");
                    strcpy(inventario[i].Descrizione, "Una lancia di ferro");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 26;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 40)
        {
            pg->Gold -= 40;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia d'acciaio");
                    strcpy(inventario[i].Descrizione, "Una lancia d'acciaio");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 40;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 36;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 50)
        {
            pg->Gold -= 50;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia d'argento");
                    strcpy(inventario[i].Descrizione, "Una lancia d'argento");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 50;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 46;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 60)
        {
            pg->Gold -= 60;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[I]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 60;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 56;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia magica[I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 70)
        {
            pg->Gold -= 70;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[II]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 70;
                    inventario[i].Durability = 200;
                    inventario[i].Damage = 66;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia magica[II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 80)
        {
            pg->Gold -= 80;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[III]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 80;
                    inventario[i].Durability = 300;
                    inventario[i].Damage = 76;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia magica[III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 90)
        {
            pg->Gold -= 90;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[IV]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 90;
                    inventario[i].Durability = 400;
                    inventario[i].Damage = 86;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia magica[IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 100)
        {
            pg->Gold -= 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[V]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 500;
                    inventario[i].Damage = 96;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la lancia magica[V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_mazze(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~-[NEGOZIO]-~---~---~---+\n");
        printf("> (1) Mazza di legno {15 G}\n");
        printf("> (2) Mazza di rame {25 G}\n");
        printf("> (3) Mazza di ferro {35 G}\n");
        printf("> (4) Mazza d'acciaio {45 G}\n");
        printf("> (5) Mazza d'argento {55 G}\n");
        printf("> (6) Mazza magica[I] {65 G}\n");
        printf("> (7) Mazza magica[II] {75 G}\n");
        printf("> (8) Mazza magica[III] {85 G}\n");
        printf("> (9) Mazza magica[IV] {95 G}\n");
        printf("> (10) Mazza magica[V] {105 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d G]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 15)
        {
            pg->Gold -= 15;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza di legno");
                    strcpy(inventario[i].Descrizione, "Una mazza di legno");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 8;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza di rame");
                    strcpy(inventario[i].Descrizione, "Una mazza di rame");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 18;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza di ferro");
                    strcpy(inventario[i].Descrizione, "Una mazza di ferro");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 28;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }

        break;
    case 4:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza d'acciaio");
                    strcpy(inventario[i].Descrizione, "Una mazza d'acciaio");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 38;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza d'argento");
                    strcpy(inventario[i].Descrizione, "Una mazza d'argento");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 48;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }

        break;
    case 6:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza magica [I]");
                    strcpy(inventario[i].Descrizione, "Una mazza magica [I]");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 58;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza magica [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [I]!\n");
        Sleep(1000);
        break;
    case 7:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza magica [II]");
                    strcpy(inventario[i].Descrizione, "Una mazza magica [II]");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 68;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza magica [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza magica [III]");
                    strcpy(inventario[i].Descrizione, "Una mazza magica [III]");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 78;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza magica [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza magica [IV]");
                    strcpy(inventario[i].Descrizione, "Una mazza magica [IV]");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 88;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza magica [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 105)
        {
            pg->Gold -= 105;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Mazza magica [V]");
                    strcpy(inventario[i].Descrizione, "Una mazza magica [V]");
                    inventario[i].Tipo = "Mazza";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 105;
                    inventario[i].Durability = 110;
                    inventario[i].Damage = 98;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la mazza magica [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_pugnali(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Pugnale di legno {2 G}\n");
        printf("> (2) Pugnale di rame {12 G}\n");
        printf("> (3) Pugnale di ferro {22 G}\n");
        printf("> (4) Pugnale d'acciaio {32 G}\n");
        printf("> (5) Pugnale d'argento {42 G}\n");
        printf("> (6) Pugnale magica[I] {52 G}\n");
        printf("> (7) Pugnale magica[II] {62 G}\n");
        printf("> (8) Pugnale magica[III] {72 G}\n");
        printf("> (9) Pugnale magica[IV] {82 G}\n");
        printf("> (10) Pugnale magica[V] {92 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d G]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 2)
        {
            pg->Gold -= 2;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale di legno");
                    strcpy(inventario[i].Descrizione, "Un pugnale di legno");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 2;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 4;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 12)
        {
            pg->Gold -= 12;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale di rame");
                    strcpy(inventario[i].Descrizione, "Un pugnale di rame");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 12;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 14;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }

        break;
    case 3:
        if (pg->Gold >= 22)
        {
            pg->Gold -= 22;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale di ferro");
                    strcpy(inventario[i].Descrizione, "Un pugnale di ferro");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 22;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 24;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }

        break;
    case 4:
        if (pg->Gold >= 32)
        {
            pg->Gold -= 32;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale d'acciaio");
                    strcpy(inventario[i].Descrizione, "Un pugnale d'acciaio");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 32;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 34;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 42)
        {
            pg->Gold -= 42;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale d'argento");
                    strcpy(inventario[i].Descrizione, "Un pugnale d'argento");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 42;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 44;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 52)
        {
            pg->Gold -= 52;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale magico [I]");
                    strcpy(inventario[i].Descrizione, "Un pugnale magico [I]");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 52;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 54;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale magico [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 62)
        {
            pg->Gold -= 62;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale magico [II]");
                    strcpy(inventario[i].Descrizione, "Un pugnale magico [II]");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 62;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 64;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale magico [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 72)
        {
            pg->Gold -= 72;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale magico [III]");
                    strcpy(inventario[i].Descrizione, "Un pugnale magico [III]");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 72;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 74;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale magico [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 82)
        {
            pg->Gold -= 82;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale magico [IV]");
                    strcpy(inventario[i].Descrizione, "Un pugnale magico [IV]");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 82;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 84;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale magico [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 92)
        {
            pg->Gold -= 92;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pugnale magico [V]");
                    strcpy(inventario[i].Descrizione, "Un pugnale magico [V]");
                    inventario[i].Tipo = "Pugnale";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 92;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 94;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato il pugnale magico [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_archi(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Arco di legno {25 G}\n");
        printf("> (2) Arco di rame {35 G}\n");
        printf("> (3) Arco di ferro {45 G}\n");
        printf("> (4) Arco d'acciaio {55 G}\n");
        printf("> (5) Arco d'argento {65 G}\n");
        printf("> (6) Arco magico[I] {75 G}\n");
        printf("> (7) Arco magico[II] {85 G}\n");
        printf("> (8) Arco magico[III] {95 G}\n");
        printf("> (9) Arco magica[IV] {105 G}\n");
        printf("> (10) Arco magico[V] {115 G}\n");
        printf("> (11) Frecce \n");
        printf("> (12) Indietro \n");
        printf("+---~---~---~--[%d G]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 12);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco di legno");
                    strcpy(inventario[i].Descrizione, "Un arco di legno, non molto potente ma comunque utile");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 10;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco di legno" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco di rame");
                    strcpy(inventario[i].Descrizione, "Un arco di rame, non molto potente ma comunque utile");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 20;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco di rame" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco di ferro");
                    strcpy(inventario[i].Descrizione, "Un arco di ferro, un po' piu' potente dell'arco di rame");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 30;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco di ferro" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco d'acciaio");
                    strcpy(inventario[i].Descrizione, "Un arco d'acciaio, molto piu' potente dell'arco di ferro");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 40;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco d'acciaio" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco d'argento");
                    strcpy(inventario[i].Descrizione, "Un arco d'argento, molto piu' potente dell'arco d'acciaio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 50;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco d'argento" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco magico [I]");
                    strcpy(inventario[i].Descrizione, "Un arco magico, molto potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 60;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco magico [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco magico [I]" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco magico [II]");
                    strcpy(inventario[i].Descrizione, "Un arco magico, molto piu' potente dell'arco magico [I]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 70;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco magico [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco magico [II]" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco magico [III]");
                    strcpy(inventario[i].Descrizione, "Un arco magico, molto forte");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 80;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco magico [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco magico [III]" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 105)
        {
            pg->Gold -= 105;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco magico [IV]");
                    strcpy(inventario[i].Descrizione, "Un arco magico, molto potente, ma non puo' essere usato da tutti");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 105;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 90;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco magico [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco magico [IV]" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 115)
        {
            pg->Gold -= 115;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Arco magico [V]");
                    strcpy(inventario[i].Descrizione, "Un arco magico, molto potente, difficile da usare");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 115;
                    inventario[i].Durability = 0;
                    inventario[i].Damage = 100;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'arco magico [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Arco magico [V]" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        if (pg->Gold >= 2)
        {
            pg->Gold -= 2;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "Frecce" || inventario[i].nome == "vuoto")
                {
                    pg->Gold = pg->Gold - inventario[i].Value;
                    strcpy(inventario[i].nome, "Frecce");
                    strcpy(inventario[i].Descrizione, "Frecce per l'arco");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 2;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char frecce_da_comprare[1000] = ("Ogni pacco di frecce ne ha 20, quante ne vuoi comprare?");
                    print_decorate_sentence(frecce_da_comprare);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    pg->Gold = pg->Gold - inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "Frecce" && i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 12:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_armi(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[ARMI]~---~---~---+\n");
        printf("> (1) Spade \n");
        printf("> (2) Asce \n");
        printf("> (3) Lance \n");
        printf("> (5) Mazze \n");
        printf("> (5) Pugnali \n");
        printf("> (6) Archi e frecce \n");
        printf("> (7) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 7);
    switch (scelta)
    {
    case 1:
        compra_spade(pg, inventario, equipaggiamento);
        break;
    case 2:
        compra_asce(pg, inventario, equipaggiamento);
        break;
    case 3:
        compra_lance(pg, inventario, equipaggiamento);
        break;
    case 4:
        compra_mazze(pg, inventario, equipaggiamento);
        break;
    case 5:
        compra_pugnali(pg, inventario, equipaggiamento);
        break;
    case 6:
        compra_archi(pg, inventario, equipaggiamento);
        break;
    case 7:
        break;
    }
}

void vendi_armi(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Arma")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    else if (inventario[scelta - 1].Tipo == "Arma")
    {
        pg->Gold = pg->Gold + (inventario[scelta - 1].Value * inventario[scelta - 1].Quantity);
        strcpy(inventario[scelta - 1].nome, "vuoto");
        strcpy(inventario[scelta - 1].Descrizione, "vuoto");
        inventario[scelta - 1].Tipo = "vuoto";
        inventario[scelta - 1].Rarity = "vuoto";
        inventario[scelta - 1].Value = 0;
        inventario[scelta - 1].Durability = 0;
        inventario[scelta - 1].Damage = 0;
        SetColor(2); // verde
        printf("Hai venduto la %s!\n", inventario[scelta - 1].nome);
        Sleep(1000);
    }
    else
    {
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_elmi(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~-[ELMI]-~---~---~---+\n");
        printf("> (1) Elmo di cuio {5 G}\n");
        printf("> (2) Elmo di rame {15 G}\n");
        printf("> (3) Elmo di ferro {25 G}\n");
        printf("> (4) Elmo d'acciaio {35 G}\n");
        printf("> (5) Elmo d'argento {45 G}\n");
        printf("> (6) Elmo magica[I] {55 G}\n");
        printf("> (7) Elmo magica[II] {65 G}\n");
        printf("> (8) Elmo magica[III] {75 G}\n");
        printf("> (9) Elmo magica[IV] {85 G}\n");
        printf("> (10) Elmo magica[V] {95 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo di legno");
                    strcpy(inventario[i].Descrizione, "Elmo di legno, fa quello che deve fare.");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo di legno!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 20)
        {
            pg->Gold -= 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo di rame");
                    strcpy(inventario[i].Descrizione, "Elmo di rame, non molto potente ma comunque utile");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 30)
        {
            pg->Gold -= 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo di ferro");
                    strcpy(inventario[i].Descrizione, "Elmo di ferro, di buona qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 40)
        {
            pg->Gold -= 40;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo d'acciaio");
                    strcpy(inventario[i].Descrizione, "Elmo d'acciaio, utilizzato da molti guerrieri");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 40;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 50)
        {
            pg->Gold -= 50;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo d'argento");
                    strcpy(inventario[i].Descrizione, "Elmo d'argento, una delle migliori aramture");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 50;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 60)
        {
            pg->Gold -= 60;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo magica [I]");
                    strcpy(inventario[i].Descrizione, "Elmo magico, molto potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 60;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo magica [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 70)
        {
            pg->Gold -= 70;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo magica [II]");
                    strcpy(inventario[i].Descrizione, "Elmo magico, di altissima qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 70;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo magica [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 80)
        {
            pg->Gold -= 80;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo magica [III]");
                    strcpy(inventario[i].Descrizione, "Elmo magica, la piu' potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 80;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo magica [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 90)
        {
            pg->Gold -= 90;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo magico [IV]");
                    strcpy(inventario[i].Descrizione, "Elmo magico, il piu' potente quasi fra tutti");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 90;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo magico [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 100)
        {
            pg->Gold -= 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Elmo magico [V]");
                    strcpy(inventario[i].Descrizione, "Elmo magica, il piu' potente fra tutti");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato l'elmo magico [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_corazze(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        printf("> (1) Corazza di cuio {5 G}\n");
        printf("> (2) Corazza di rame {15 G}\n");
        printf("> (3) Corazza di ferro {25 G}\n");
        printf("> (4) Corazza d'acciaio {35 G}\n");
        printf("> (5) Corazza d'argento {45 G}\n");
        printf("> (6) Corazza magica[I] {55 G}\n");
        printf("> (7) Corazza magica[II] {65 G}\n");
        printf("> (8) Corazza magica[III] {75 G}\n");
        printf("> (9) Corazza magica[IV] {85 G}\n");
        printf("> (10) Corazza magica[V] {95 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza di cuio");
                    strcpy(inventario[i].Descrizione, "Corazza di cuio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 5;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza di cuio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 20)
        {
            pg->Gold -= 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza di rame");
                    strcpy(inventario[i].Descrizione, "Corazza di rame");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 30)
        {
            pg->Gold -= 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza di ferro");
                    strcpy(inventario[i].Descrizione, "Corazza di ferro");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 40)
        {
            pg->Gold -= 40;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza d'acciaio");
                    strcpy(inventario[i].Descrizione, "Corazza d'acciaio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 50)
        {
            pg->Gold -= 50;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza d'argento");
                    strcpy(inventario[i].Descrizione, "Corazza d'argento");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 60)
        {
            pg->Gold -= 60;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza magica [I]");
                    strcpy(inventario[i].Descrizione, "Corazza magica [I]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza magica [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 70)
        {
            pg->Gold -= 70;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza magica [II]");
                    strcpy(inventario[i].Descrizione, "Corazza magica [II]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza magica [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 80)
        {
            pg->Gold -= 80;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza magica [III]");
                    strcpy(inventario[i].Descrizione, "Corazza magica [III]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza magica [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 90)
        {
            pg->Gold -= 90;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza magica [IV]");
                    strcpy(inventario[i].Descrizione, "Corazza magica [IV]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza magica [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 100)
        {
            pg->Gold -= 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Corazza magica [V]");
                    strcpy(inventario[i].Descrizione, "Corazza magica [V]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato la corazza magica [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_pantaloni(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[PANTALONI]~---~---~---+\n");
        printf("> (1) Pantaloni di cuio {5 G}\n");
        printf("> (2) Pantaloni di rame {15 G}\n");
        printf("> (3) Pantaloni di ferro {25 G}\n");
        printf("> (4) Pantaloni d'acciaio {35 G}\n");
        printf("> (5) Pantaloni d'argento {45 G}\n");
        printf("> (6) Pantaloni magici[I] {55 G}\n");
        printf("> (7) Pantaloni magici[II] {65 G}\n");
        printf("> (8) Pantaloni magici[III] {75 G}\n");
        printf("> (9) Pantaloni magici[IV] {85 G}\n");
        printf("> (10) Pantaloni magici[V] {95 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[ %d G]--~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 5)
        {
            pg->Gold -= 5;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni di cuio");
                    strcpy(inventario[i].Descrizione, "Pantaloni di cuio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 5;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni di cuio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 15)
        {
            pg->Gold -= 15;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni di rame");
                    strcpy(inventario[i].Descrizione, "Pantaloni di rame");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni di ferro");
                    strcpy(inventario[i].Descrizione, "Pantaloni di ferro");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni d'acciaio");
                    strcpy(inventario[i].Descrizione, "Pantaloni d'acciaio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni d'argento");
                    strcpy(inventario[i].Descrizione, "Pantaloni d'argento");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni magici [I]");
                    strcpy(inventario[i].Descrizione, "Pantaloni magici [I]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni magici [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni magici [II]");
                    strcpy(inventario[i].Descrizione, "Pantaloni magici [II]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni magici [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni magici [III]");
                    strcpy(inventario[i].Descrizione, "Pantaloni magici [III]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni magici [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni magici [IV]");
                    strcpy(inventario[i].Descrizione, "Pantaloni magici [IV]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni magici [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Pantaloni magici [V]");
                    strcpy(inventario[i].Descrizione, "Pantaloni magici [V]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato i pantaloni magici [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_stivali(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[STIVALI]~---~---~---+\n");
        printf("> (1) Stivali di cuio {5 G}\n");
        printf("> (2) Stivali di rame {15 G}\n");
        printf("> (3) Stivali di ferro {25 G}\n");
        printf("> (4) Stivali d'acciaio {35 G}\n");
        printf("> (5) Stivali d'argento {45 G}\n");
        printf("> (6) Stivali magici[I] {55 G}\n");
        printf("> (7) Stivali magici[II] {65 G}\n");
        printf("> (8) Stivali magici[III] [75 G}\n");
        printf("> (9) Stivali magici[IV] {85 G}\n");
        printf("> (10) Stivali magici[V] {95 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 5)
        {
            pg->Gold -= 5;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali di cuio");
                    strcpy(inventario[i].Descrizione, "Stivali di cuio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 5;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali di cuio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 15)
        {
            pg->Gold -= 15;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali di rame");
                    strcpy(inventario[i].Descrizione, "Stivali di rame");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali di ferro");
                    strcpy(inventario[i].Descrizione, "Stivali di ferro");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali d'acciaio");
                    strcpy(inventario[i].Descrizione, "Stivali d'acciaio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali d'argento");
                    strcpy(inventario[i].Descrizione, "Stivali d'argento");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali magici [I]");
                    strcpy(inventario[i].Descrizione, "Stivali magici [I]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali magici [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali magici [II]");
                    strcpy(inventario[i].Descrizione, "Stivali magici [II]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali magici [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali magici [III]");
                    strcpy(inventario[i].Descrizione, "Stivali magici [III]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali magici [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali magici [IV]");
                    strcpy(inventario[i].Descrizione, "Stivali magici [IV]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali magici [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Stivali magici [V]");
                    strcpy(inventario[i].Descrizione, "Stivali magici [V]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Stivali magici [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_scudi(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~-[SCUDI]-~---~---~---+\n");
        printf("> (1) Scudi di cuio {5 G}\n");
        printf("> (2) Scudi di rame {15 G}\n");
        printf("> (3) Scudi di ferro {25 G}\n");
        printf("> (4) Scudi d'acciaio {35 G}\n");
        printf("> (5) Scudi d'argento {45 G}\n");
        printf("> (6) Scudi magici[I] {55 G}\n");
        printf("> (7) Scudi magici[II] {65 G}\n");
        printf("> (8) Scudi magici[III] {75 G}\n");
        printf("> (9) Scudi magici[IV] {85 G}\n");
        printf("> (10) Scudi magici[V] {95 G}\n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 5)
        {
            pg->Gold -= 5;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi di cuio");
                    strcpy(inventario[i].Descrizione, "Scudi di cuio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 5;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi di cuio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 15)
        {
            pg->Gold -= 15;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi di rame");
                    strcpy(inventario[i].Descrizione, "Scudi di rame");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 15;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi di rame!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 25)
        {
            pg->Gold -= 25;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi di ferro");
                    strcpy(inventario[i].Descrizione, "Scudi di ferro");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 25;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi di ferro!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 4:
        if (pg->Gold >= 35)
        {
            pg->Gold -= 35;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi d'acciaio");
                    strcpy(inventario[i].Descrizione, "Scudi d'acciaio");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 35;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi d'acciaio!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 5:
        if (pg->Gold >= 45)
        {
            pg->Gold -= 45;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi d'argento");
                    strcpy(inventario[i].Descrizione, "Scudi d'argento");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 45;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi d'argento!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 6:
        if (pg->Gold >= 55)
        {
            pg->Gold -= 55;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi magici [I]");
                    strcpy(inventario[i].Descrizione, "Scudi magici [I]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 55;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi magici [I]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 7:
        if (pg->Gold >= 65)
        {
            pg->Gold -= 65;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi magici [II]");
                    strcpy(inventario[i].Descrizione, "Scudi magici [II]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 65;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi magici [II]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 8:
        if (pg->Gold >= 75)
        {
            pg->Gold -= 75;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi magici [III]");
                    strcpy(inventario[i].Descrizione, "Scudi magici [III]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 75;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi magici [III]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 9:
        if (pg->Gold >= 85)
        {
            pg->Gold -= 85;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi magici [IV]");
                    strcpy(inventario[i].Descrizione, "Scudi magici [IV]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 85;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi magici [IV]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 10:
        if (pg->Gold >= 95)
        {
            pg->Gold -= 95;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Scudi magici [V]");
                    strcpy(inventario[i].Descrizione, "Scudi magici [V]");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 95;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 0;
                    inventario[i].Quantity = 1;
                    pg->Gold = pg->Gold + inventario[i].Value;
                    SetColor(2); // verde
                    printf("Hai comprato gli Scudi magici [V]!\n");
                    Sleep(1000);
                    break;
                }
                else if (inventario[i].nome != "vuoto" && i == SIZE_INV - 1)
                {
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza soldi!\n");
            Sleep(1000);
        }
        break;
    case 11:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_armature(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[ARMATURE]~---~---~---+\n");
        printf("> (1) Elmi \n");
        printf("> (2) Corazze \n");
        printf("> (3) Pantaloni \n");
        printf("> (4) Stivali \n");
        printf("> (5) Scudo \n");
        printf("> (6) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 6);
    switch (scelta)
    {
    case 1:
        compra_elmi(pg, inventario, equipaggiamento);
        break;
    case 2:
        compra_corazze(pg, inventario, equipaggiamento);
        break;
    case 3:
        compra_pantaloni(pg, inventario, equipaggiamento);
        break;
    case 4:
        compra_stivali(pg, inventario, equipaggiamento);
        break;
    case 5:
        compra_scudi(pg, inventario, equipaggiamento);
        break;
    case 6:
        break;
    }
}

void vendi_armature(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Corazza" || inventario[i].Tipo == "Elmo" || inventario[i].Tipo == "Pantaloni" || inventario[i].Tipo == "Stivali" || inventario[i].Tipo == "Scudo")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    else if (inventario[scelta - 1].Tipo == "Corazza" || inventario[scelta - 1].Tipo == "Elmo" || inventario[scelta - 1].Tipo == "Pantaloni" || inventario[scelta - 1].Tipo == "Stivali" || inventario[scelta - 1].Tipo == "Scudo")
    {
        pg->Gold = pg->Gold + inventario[scelta - 1].Value;
        strcpy(inventario[scelta - 1].nome, "vuoto");
        strcpy(inventario[scelta - 1].Descrizione, "vuoto");
        inventario[scelta - 1].Tipo = "vuoto";
        inventario[scelta - 1].Rarity = "vuoto";
        inventario[scelta - 1].Value = 0;
        inventario[scelta - 1].Durability = 0;
        inventario[scelta - 1].Damage = 0;
        SetColor(2); // verde
        printf("Hai venduto la %s!\n", inventario[scelta - 1].nome);
        Sleep(1000);
    }
    else
    {
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_pozioni_vita(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[POZIONI DI VITA]~---~---~---+\n");
        printf("> (1) Pozione di vita (I) {10 G}\n");
        printf("> (2) Pozione di vita (II) {20 G}\n");
        printf("> (3) Pozione di vita (II) {30 G}\n");
        printf("> (4) Indietro \n");
        printf("+---~---~---~[ %d G]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 4);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 10)
        {
            pg->Gold = pg->Gold - 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di vita (1)");
                    strcpy(inventario[i].Descrizione, "Ripristina 10 punti vita");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_vita_1[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_vita_1);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 20)
        {
            pg->Gold = pg->Gold - 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0 || strcmp(inventario[i].nome, "Pozione di vita (2)") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di vita (2)");
                    strcpy(inventario[i].Descrizione, "Ripristina 20 punti vita");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20 + inventario[i].Value;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_vita_2[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_vita_2);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    ;
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 30)
        {
            pg->Gold = pg->Gold - 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di vita (3)");
                    strcpy(inventario[i].Descrizione, "Ripristina 30 punti vita");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_vita_3[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_vita_3);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 4:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
        break;
    }
}

void compra_pozioni_mana(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[POZIONI]~---~---~---+\n");
        printf("> (1) Pozione di mana (I) {10 G}\n");
        printf("> (2) Pozione di mana (II) {20 G}\n");
        printf("> (3) Pozione di mana (III) {30 G}\n");
        printf("> (4) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 4);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 10)
        {
            pg->Gold = pg->Gold - 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di mana (1)");
                    strcpy(inventario[i].Descrizione, "Ripristina 10 punti mana");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_mana_1[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_mana_1);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato la X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 20)
        {
            pg->Gold = pg->Gold - 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di mana (2)");
                    strcpy(inventario[i].Descrizione, "Ripristina 20 punti mana");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_mana_2[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_mana_2);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 3:
        if (pg->Gold >= 30)
        {
            pg->Gold = pg->Gold - 30;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di mana (3)");
                    strcpy(inventario[i].Descrizione, "Ripristina 30 punti mana");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 1;
                    inventario[i].Damage = 0;
                    char pozione_di_mana_3[SIZE_SENTENCE] = ("Qunte ne vuoi comprare?");
                    print_decorate_sentence(pozione_di_mana_3);
                    scanf("%d", &inventario[i].Quantity + inventario[i].Quantity);
                    SetColor(2); // verde
                    printf("Hai comprato X%d %s!\n", inventario[i].Quantity, inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 4:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_pozioni(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[POZIONI]~---~---~---+\n");
        printf("> (1) Pozioni di vita \n");
        printf("> (2) Pozioni di mana \n");
        printf("> (3) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 3);
    switch (scelta)
    {
    case 1:
        compra_pozioni_vita(pg, inventario, equipaggiamento);
        break;
    case 2:
        compra_pozioni_mana(pg, inventario, equipaggiamento);
        break;
    case 3:
        break;
    }
}

void vendi_pozioni(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Pozione")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    else if (inventario[scelta - 1].Tipo == "Pozione")
    {
        pg->Gold = pg->Gold + (inventario[scelta - 1].Value * inventario[scelta - 1].Quantity);
        strcpy(inventario[scelta - 1].nome, "vuoto");
        strcpy(inventario[scelta - 1].Descrizione, "vuoto");
        inventario[scelta - 1].Tipo = "vuoto";
        inventario[scelta - 1].Rarity = "vuoto";
        inventario[scelta - 1].Value = 0;
        inventario[scelta - 1].Durability = 0;
        inventario[scelta - 1].Damage = 0;
        SetColor(2); // verde
        printf("Hai venduto la %s!\n", inventario[scelta - 1].nome);
        Sleep(1000);
    }
    else
    {
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_oggetti_speciali(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[OGGETTI SPECIALI]~---~---~---+\n");
        printf("> (1) Elmo nero decorativo \n");
        printf("> (2) Mantello dei mille occhi \n");
        printf("> (3) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 1);
    switch (scelta)
    {
    case 1:
        if (pg->Gold >= 100)
        {
            pg->Gold = pg->Gold - 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Elmo nero decorativo");
                    strcpy(inventario[i].Descrizione, "Appartiene ad uno degli amici dello sviluppatore...Lo chiamavano Ebano");
                    inventario[i].Tipo = "Speciale";
                    inventario[i].Rarity = "Leggendario";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 999;
                    inventario[i].Damage = 0;
                    SetColor(2); // verde
                    printf("Hai comprato la %s!\n", inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 2:
        if (pg->Gold >= 100)
        {
            pg->Gold = pg->Gold - 100;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Mantello dei mille occhi");
                    strcpy(inventario[i].Descrizione, "Appartiene ad uno degli amici dello sviluppatore...Lo chiamavano Edward");
                    inventario[i].Tipo = "Speciale";
                    inventario[i].Rarity = "Leggendario";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 999;
                    inventario[i].Damage = 0;
                    SetColor(2); // verde
                    printf("Hai comprato la %s!\n", inventario[i].nome);
                    Sleep(1000);
                    break;
                }
                else if (strcmp(inventario[i].nome, "vuoto") > 0 || i == SIZE_INV - 1)
                {
                    SetColor(4); // rosso
                    printf("Inventario pieno!\n");
                    Sleep(1000);
                }
            }
        }
        else
        {
            SetColor(4); // rosso
            printf("Non hai abbastanza oro!\n");
            Sleep(1000);
        }
        break;
    case 3:
        break;
    }
}

void vendi_oggetti_speciali(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Speciale")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    else if (inventario[scelta - 1].Tipo == "Speciale")
    {
        pg->Gold = pg->Gold + inventario[scelta - 1].Value;
        strcpy(inventario[scelta - 1].nome, "vuoto");
        strcpy(inventario[scelta - 1].Descrizione, "vuoto");
        inventario[scelta - 1].Tipo = "vuoto";
        inventario[scelta - 1].Rarity = "vuoto";
        inventario[scelta - 1].Value = 0;
        inventario[scelta - 1].Durability = 0;
        inventario[scelta - 1].Damage = 0;
        SetColor(2); // verde
        printf("Hai venduto la %s!\n", inventario[scelta - 1].nome);
        Sleep(1000);
    }
    else
    {
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void compra_oggetti(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[OGGETTI]~---~---~---+\n");
        printf("> (1) Armi \n");
        printf("> (2) Armature \n");
        printf("> (3) Pozioni \n");
        printf("> (4) Oggetti speciali \n");
        printf("> (5) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 5);
    switch (scelta)
    {
    case 1:
        compra_armi(pg, inventario, equipaggiamento);
        break;
    case 2:
        compra_armature(pg, inventario, equipaggiamento);
        break;
    case 3:
        compra_pozioni(pg, inventario, equipaggiamento);
        break;
    case 4:
        compra_oggetti_speciali(pg, inventario, equipaggiamento);
        break;
    case 5:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void vendi_oggetti(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[OGGETTI]~---~---~---+\n");
        printf("> (1) Armi \n");
        printf("> (2) Armature \n");
        printf("> (3) Pozioni \n");
        printf("> (4) Oggetti speciali \n");
        printf("> (5) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 5);
    switch (scelta)
    {
    case 1:
        vendi_armi(pg, inventario, equipaggiamento);
        break;
    case 2:
        vendi_armature(pg, inventario, equipaggiamento);
        break;
    case 3:
        vendi_pozioni(pg, inventario, equipaggiamento);
        break;
    case 4:
        vendi_oggetti_speciali(pg, inventario, equipaggiamento);
        break;
    case 5:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void vend_oggetti(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[OGGETTI]~---~---~---+\n");
        printf("> (1) Armi \n");
        printf("> (2) Armature \n");
        printf("> (3) Pozioni \n");
        printf("> (4) Oggetti speciali \n");
        printf("> (5) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n", pg->Gold);
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 5);
    switch (scelta)
    {
    case 1:
        vendi_armi(pg, inventario, equipaggiamento);
        break;
    case 2:
        vendi_armature(pg, inventario, equipaggiamento);
        break;
    case 3:
        vendi_pozioni(pg, inventario, equipaggiamento);
        break;
    case 4:
        vendi_oggetti_speciali(pg, inventario, equipaggiamento);
        break;
    case 5:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void negozio(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Compra oggetti \n");
        printf("> (2) Vendi oggetti \n");
        printf("> (3) Indietro \n");
    } while (scelta < 1 || scelta > 3);
    switch (scelta)
    {
    case 1:
        compra_oggetti(pg, inventario, equipaggiamento);
        break;
    case 2:
        vend_oggetti(pg, inventario, equipaggiamento);
        break;
    case 3:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void equipaggiamento_arma(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CORAZZE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Arma")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~--[ § ]--~---~---~---+\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    // se l'ogetto è di tipo arma lo scambia con quello in posizione 1
    if (inventario[scelta - 1].Tipo == "Arma")
    {
        if (equipaggiamento[1].Tipo == "Scudo")
        {
            O temp;
            printf("Vuoi scambiare %s con %s? (Y) Si (N) No \n", inventario[scelta - 1].nome, equipaggiamento[1].nome);
            char scelta_2;
            scanf("%d", &scelta_2);
            switch (scelta_2)
            {
            case 'Y':
                strcpy(temp.nome, equipaggiamento[1].nome);
                strcpy(temp.Descrizione, equipaggiamento[1].Descrizione);
                temp.Tipo = equipaggiamento[1].Tipo;
                temp.Rarity = equipaggiamento[1].Rarity;
                temp.Value = equipaggiamento[1].Value;
                temp.Durability = equipaggiamento[1].Durability;
                temp.Damage = equipaggiamento[1].Damage;
                temp.Quantity = equipaggiamento[1].Quantity;

                strcpy(equipaggiamento[1].nome, inventario[scelta - 1].nome);
                strcpy(equipaggiamento[1].Descrizione, inventario[scelta - 1].Descrizione);
                equipaggiamento[1].Tipo = inventario[scelta - 1].Tipo;
                equipaggiamento[1].Rarity = inventario[scelta - 1].Rarity;
                equipaggiamento[1].Value = inventario[scelta - 1].Value;
                equipaggiamento[1].Durability = inventario[scelta - 1].Durability;
                equipaggiamento[1].Damage = inventario[scelta - 1].Damage;
                equipaggiamento[1].Quantity = inventario[scelta - 1].Quantity;

                strcpy(inventario[scelta - 1].nome, temp.nome);
                strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
                inventario[scelta - 1].Tipo = temp.Tipo;
                inventario[scelta - 1].Rarity = temp.Rarity;
                inventario[scelta - 1].Value = temp.Value;
                inventario[scelta - 1].Durability = temp.Durability;
                inventario[scelta - 1].Damage = temp.Damage;
                inventario[scelta - 1].Quantity = temp.Quantity;
                break;
            case 'N':
                strcpy(temp.nome, equipaggiamento[0].nome);
                strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
                temp.Tipo = equipaggiamento[0].Tipo;
                temp.Rarity = equipaggiamento[0].Rarity;
                temp.Value = equipaggiamento[0].Value;
                temp.Durability = equipaggiamento[0].Durability;
                temp.Damage = equipaggiamento[0].Damage;
                temp.Quantity = equipaggiamento[0].Quantity;

                strcpy(equipaggiamento[0].nome, inventario[scelta - 1].nome);
                strcpy(equipaggiamento[0].Descrizione, inventario[scelta - 1].Descrizione);
                equipaggiamento[0].Tipo = inventario[scelta - 1].Tipo;
                equipaggiamento[0].Rarity = inventario[scelta - 1].Rarity;
                equipaggiamento[0].Value = inventario[scelta - 1].Value;
                equipaggiamento[0].Durability = inventario[scelta - 1].Durability;
                equipaggiamento[0].Damage = inventario[scelta - 1].Damage;
                equipaggiamento[0].Quantity = inventario[scelta - 1].Quantity;

                strcpy(inventario[scelta - 1].nome, temp.nome);
                strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
                inventario[scelta - 1].Tipo = temp.Tipo;
                inventario[scelta - 1].Rarity = temp.Rarity;
                inventario[scelta - 1].Value = temp.Value;
                inventario[scelta - 1].Durability = temp.Durability;
                inventario[scelta - 1].Damage = temp.Damage;
                inventario[scelta - 1].Quantity = temp.Quantity;
                break;
            case 'y':
                strcpy(temp.nome, equipaggiamento[1].nome);
                strcpy(temp.Descrizione, equipaggiamento[1].Descrizione);
                temp.Tipo = equipaggiamento[1].Tipo;
                temp.Rarity = equipaggiamento[1].Rarity;
                temp.Value = equipaggiamento[1].Value;
                temp.Durability = equipaggiamento[1].Durability;
                temp.Damage = equipaggiamento[1].Damage;
                temp.Quantity = equipaggiamento[1].Quantity;

                strcpy(equipaggiamento[1].nome, inventario[scelta - 1].nome);
                strcpy(equipaggiamento[1].Descrizione, inventario[scelta - 1].Descrizione);
                equipaggiamento[1].Tipo = inventario[scelta - 1].Tipo;
                equipaggiamento[1].Rarity = inventario[scelta - 1].Rarity;
                equipaggiamento[1].Value = inventario[scelta - 1].Value;
                equipaggiamento[1].Durability = inventario[scelta - 1].Durability;
                equipaggiamento[1].Damage = inventario[scelta - 1].Damage;
                equipaggiamento[1].Quantity = inventario[scelta - 1].Quantity;

                strcpy(inventario[scelta - 1].nome, temp.nome);
                strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
                inventario[scelta - 1].Tipo = temp.Tipo;
                inventario[scelta - 1].Rarity = temp.Rarity;
                inventario[scelta - 1].Value = temp.Value;
                inventario[scelta - 1].Durability = temp.Durability;
                inventario[scelta - 1].Damage = temp.Damage;
                inventario[scelta - 1].Quantity = temp.Quantity;
                break;
            case 'n':
                strcpy(temp.nome, equipaggiamento[0].nome);
                strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
                temp.Tipo = equipaggiamento[0].Tipo;
                temp.Rarity = equipaggiamento[0].Rarity;
                temp.Value = equipaggiamento[0].Value;
                temp.Durability = equipaggiamento[0].Durability;
                temp.Damage = equipaggiamento[0].Damage;
                temp.Quantity = equipaggiamento[0].Quantity;

                strcpy(equipaggiamento[0].nome, inventario[scelta - 1].nome);
                strcpy(equipaggiamento[0].Descrizione, inventario[scelta - 1].Descrizione);
                equipaggiamento[0].Tipo = inventario[scelta - 1].Tipo;
                equipaggiamento[0].Rarity = inventario[scelta - 1].Rarity;
                equipaggiamento[0].Value = inventario[scelta - 1].Value;
                equipaggiamento[0].Durability = inventario[scelta - 1].Durability;
                equipaggiamento[0].Damage = inventario[scelta - 1].Damage;
                equipaggiamento[0].Quantity = inventario[scelta - 1].Quantity;

                strcpy(inventario[scelta - 1].nome, temp.nome);
                strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
                inventario[scelta - 1].Tipo = temp.Tipo;
                inventario[scelta - 1].Rarity = temp.Rarity;
                inventario[scelta - 1].Value = temp.Value;
                inventario[scelta - 1].Durability = temp.Durability;
                inventario[scelta - 1].Damage = temp.Damage;
                inventario[scelta - 1].Quantity = temp.Quantity;
            default:

                SetColor(4); // rosso
                printf("Scelta non valida!\n");
                Sleep(1000);
                break;
            }
        }
    }
    else
    {
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        strcpy(equipaggiamento[0].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[0].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[0].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[0].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[0].Value = inventario[scelta - 1].Value;
        equipaggiamento[0].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[0].Damage = inventario[scelta - 1].Damage;
        equipaggiamento[0].Quantity = inventario[scelta - 1].Quantity;

        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
        inventario[scelta - 1].Damage = temp.Damage;
        inventario[scelta - 1].Quantity = temp.Quantity;
    }
}

void equipaggiamento_armatura(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[ARMATURE]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].Tipo == "Elmo" || inventario[i].Tipo == "Corazza" || inventario[i].Tipo == "Pantaloni" || inventario[i].Tipo == "Stivali" || inventario[i].Tipo == "Scudo")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~--[ § ]--~---~---~---+\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    // se è un oggetto di tipo elmo lo scambia con quello in posizione 3
    else if (inventario[scelta - 1].Tipo == "Elmo")
    {
        // copio il vecchio elmo in un equipaggiamento temporaneo
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        // copio l'arma nell'equipaggiamento
        strcpy(equipaggiamento[3].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[3].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[3].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[3].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[3].Value = inventario[scelta - 1].Value;
        equipaggiamento[3].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[3].Damage = inventario[scelta - 1].Damage;

        // copio l'equipaggiamento temporaneo nell'inventario
        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
        inventario[scelta - 1].Damage = temp.Damage;
        inventario[scelta - 1].Quantity = temp.Quantity;
    }
    // se è un oggetto di tipo corazza lo scambia con quello in posizione 4
    else if (inventario[scelta - 1].Tipo == "Corazza")
    {
        // copio il vecchio elmo in un equipaggiamento temporaneo
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        // copio l'arma nell'equipaggiamento
        strcpy(equipaggiamento[4].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[4].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[4].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[4].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[4].Value = inventario[scelta - 1].Value;
        equipaggiamento[4].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[4].Damage = inventario[scelta - 1].Damage;

        // copio l'equipaggiamento temporaneo nell'inventario
        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
        inventario[scelta - 1].Damage = temp.Damage;
        inventario[scelta - 1].Quantity = temp.Quantity;
    }
    // se è un oggetto di tipo pantaloni lo scambia con quello in posizione 5
    else if (inventario[scelta - 1].Tipo == "Pantaloni")
    {
        // copio il vecchio elmo in un equipaggiamento temporaneo
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        // copio l'arma nell'equipaggiamento
        strcpy(equipaggiamento[5].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[5].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[5].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[5].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[5].Value = inventario[scelta - 1].Value;
        equipaggiamento[5].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[5].Damage = inventario[scelta - 1].Damage;

        // copio l'equipaggiamento temporaneo nell'inventario
        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
        inventario[scelta - 1].Damage = temp.Damage;
        inventario[scelta - 1].Quantity = temp.Quantity;
    }
    // se è un oggetto di tipo scarpe lo scambia con quello in posizione 6
    else if (inventario[scelta - 1].Tipo == "Scarpe")
    {
        // copio il vecchio elmo in un equipaggiamento temporaneo
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        // copio l'arma nell'equipaggiamento
        strcpy(equipaggiamento[6].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[6].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[6].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[6].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[6].Value = inventario[scelta - 1].Value;
        equipaggiamento[6].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[6].Damage = inventario[scelta - 1].Damage;

        // copio l'equipaggiamento temporaneo nell'inventario
        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
    }
    // se è un oggetto di tipo scudo lo scambia con quello in posizione 2
    else if (inventario[scelta - 1].Tipo == "Scudo")
    {
        // copio il vecchio elmo in un equipaggiamento temporaneo
        O temp;
        strcpy(temp.nome, equipaggiamento[0].nome);
        strcpy(temp.Descrizione, equipaggiamento[0].Descrizione);
        temp.Tipo = equipaggiamento[0].Tipo;
        temp.Rarity = equipaggiamento[0].Rarity;
        temp.Value = equipaggiamento[0].Value;
        temp.Durability = equipaggiamento[0].Durability;
        temp.Damage = equipaggiamento[0].Damage;
        temp.Quantity = equipaggiamento[0].Quantity;

        // copio l'arma nell'equipaggiamento
        strcpy(equipaggiamento[2].nome, inventario[scelta - 1].nome);
        strcpy(equipaggiamento[2].Descrizione, inventario[scelta - 1].Descrizione);
        equipaggiamento[2].Tipo = inventario[scelta - 1].Tipo;
        equipaggiamento[2].Rarity = inventario[scelta - 1].Rarity;
        equipaggiamento[2].Value = inventario[scelta - 1].Value;
        equipaggiamento[2].Durability = inventario[scelta - 1].Durability;
        equipaggiamento[2].Damage = inventario[scelta - 1].Damage;

        // copio l'equipaggiamento temporaneo nell'inventario
        strcpy(inventario[scelta - 1].nome, temp.nome);
        strcpy(inventario[scelta - 1].Descrizione, temp.Descrizione);
        inventario[scelta - 1].Tipo = temp.Tipo;
        inventario[scelta - 1].Rarity = temp.Rarity;
        inventario[scelta - 1].Value = temp.Value;
        inventario[scelta - 1].Durability = temp.Durability;
        inventario[scelta - 1].Damage = temp.Damage;
        inventario[scelta - 1].Quantity = temp.Quantity;
    }
}

void equipaggiamento_oggetto(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[EQUIPAGGIAMENTO]~---~---~---+\n");
        printf("> (1) Arma \n");
        printf("> (2) Armatura \n");
        printf("> (3) Indietro \n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 3);
    switch (scelta)
    {
    case 1:
        equipaggiamento_arma(pg, inventario, equipaggiamento);
        break;
    case 2:
        equipaggiamento_armatura(pg, inventario, equipaggiamento);
        break;
    case 3:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void cancellare_oggetto(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[CANCELLARE OGGETTO]~---~---~---+\n");
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome != "vuoto")
            {
                printf("> (%d) %s \n", i + 1, inventario[i].nome);
            }
        }
        printf("> (%d) Indietro \n", SIZE_INV + 1);
        printf("+---~---~---~--[ § ]--~---~---~---+\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > SIZE_INV + 1);
    if (scelta == SIZE_INV + 1)
    {
        return;
    }
    else if (inventario[scelta - 1].nome != "vuoto")
    {
        strcpy(inventario[scelta - 1].nome, "vuoto");
        strcpy(inventario[scelta - 1].Descrizione, "");
        inventario[scelta - 1].Tipo = "";
        inventario[scelta - 1].Rarity = "";
        inventario[scelta - 1].Value = 0;
        inventario[scelta - 1].Durability = 0;
        inventario[scelta - 1].Damage = 0;
        SetColor(2); // verde
        printf("Hai cancellato %s!\n", inventario[scelta - 1].nome);
        Sleep(1000);
    }
    else
    {
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void selezione_oggetto(ST *pg, O *inventario, O *equipaggiamento)
{
    print_zaino(inventario);
    SetColor(9); // blu
    char scelta[SIZE_SENTENCE] = ("Cosa vuoi fare? (1)Equipaggiare, (2)Cancellare, (3)Tornare indietro\n");
    print_decorate_choices(scelta);
    int scelta_oggetto;
    SetColor(7); // bianco
    scanf("%d", &scelta_oggetto);
    switch (scelta_oggetto)
    {
    case 1:
        equipaggiamento_oggetto(pg, inventario, equipaggiamento);
        break;
    case 2:
        cancellare_oggetto(pg, inventario, equipaggiamento);
        break;
    case 3:
        break;
    default:
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void zaino(ST *pg, O *inventario, O *equipaggiamento)
{
    print_zaino(inventario);
    SetColor(9); // blu
    char scelta[SIZE_SENTENCE] = ("Cosa vuoi fare? (1)Selezionare un oggetto, (2)Tornare indietro\n");
    print_decorate_choices(scelta);
    int scelta_zaino;
    SetColor(7); // bianco
    scanf("%d", &scelta_zaino);
    switch (scelta_zaino)
    {
    case 1:
        selezione_oggetto(pg, inventario, equipaggiamento);
        break;
    case 2:
        break;
    default:
        printf("Scelta non valida\n");
        break;
    }
}

void dungeon(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[DUNGEON]~---~---~---+\n");
        printf("> (1) \n");
        printf("> (2) Indietro \n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 2);
    switch (scelta)
    {
    case 1:
        dungeon_avventura(pg, inventario, equipaggiamento);
        break;
    case 2:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void avventura(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(5); // viola
        printf("+---~---~---~[AVVENTURA]~---~---~---+\n");
        printf("> (1) Entra nel Dungeon \n");
        printf("> (2) Stato Personaggio \n");
        printf("> (3) Zaino \n");
        printf("> (4) Equipaggiamento \n");
        printf("> (5) Negozio \n");
        printf("> (6) Indietro \n");
    } while (scelta < 1 || scelta > 6);
    switch (scelta)
    {
    case 1:
        dungeon(pg, inventario, equipaggiamento);
        break;
    case 2:
        stato_personaggio(pg);
        break;
    case 3:
        print_zaino(inventario);
        break;
    case 4:
        print_equipaggiamento(equipaggiamento);
        break;
    case 5:
        negozio(pg, inventario, equipaggiamento);
        break;
    case 6:
        break;
    }
}

void menu(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        SetColor(2); // verde
        printf("Benvenuto %s!\n", pg->name);
        SetColor(5); // viola
        printf("+---~---~---~[MENU]~---~---~---+\n");
        printf("> (1) Avventura \n");
        printf("> (2) Load \n");
        printf("> (3) Salva \n");
        printf("> (4) Esci \n");
        printf("+---~[HP:%d]~[%dxp]~[MP:%d]~---+\n\n", pg->Vita, pg->Exp, pg->Mana);
    } while (scelta < 1 || scelta > 4);
    switch (scelta)
    {
    case 1:
        avventura(pg, inventario, equipaggiamento);
        break;
    case 2:
        clear();
        SetColor(2); // verde
        printf("Caricamento in corso...\n");
        load(pg, inventario, equipaggiamento);
        break;
    case 3:
        clear();
        SetColor(2); // verde
        printf("Salvataggio in corso...\n");
        save(pg, inventario, equipaggiamento);
        break;
    case 4:
        clear();
        SetColor(2); // verde
        printf("Grazie per aver giocato!\n");
        exit(0);
        break;
    default:
        break;
    }
}

int main()
{
    ST pg;
    titolo_inizio();
    inserimento_nome(&pg);
    statistiche_iniziali(&pg);
    const char *Rarity[] = {"Comune", "Raro", "Epico", "Leggendario"};
    const char *Tipo[] = {"Arma", "Elmo", "Corazza", "Pantaloni", "Stivali", "Scudo", "Guarigione", "Veleno", "Buff", "Debuff", "Speciale"};
    O inventario[SIZE_INV];
    O equipaggiamento[SIZE_EQUIP];
    equipaggiamento[0].Tipo = "Arma";
    equipaggiamento[1].Tipo = "Scudo";
    equipaggiamento[2].Tipo = "Elmo";
    equipaggiamento[3].Tipo = "Corazza";
    equipaggiamento[4].Tipo = "Pantaloni";
    equipaggiamento[5].Tipo = "Stivali";
    inv_iniziale(inventario);
    equip_iniziale(&pg, equipaggiamento);
    SetColor(2); // verde
    printf("debug riuscito...");
    menu(&pg, inventario, equipaggiamento);
    return 0;
}