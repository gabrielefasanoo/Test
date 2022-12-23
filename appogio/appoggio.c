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
        printf("+---~---~---~[SPADE]~---~---~---+\n");
        printf("> (1) Spada di legno \n");
        printf("> (2) Spada di rame \n");
        printf("> (3) Spada di ferro \n");
        printf("> (4) Spada d'acciaio \n");
        printf("> (5) Spada d'argento \n");
        printf("> (6) Spada magica[I] \n");
        printf("> (7) Spada magica[II] \n");
        printf("> (8) Spada magica[III] \n");
        printf("> (9) Spada magica[IV] \n");
        printf("> (10) Spada magica[V] \n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~[ %d ]~---~---~---+\n\n", pg->Gold);
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
                    strcpy(inventario[i].nome, "Spada di legno");
                    strcpy(inventario[i].Descrizione, "Spada di legno, fa quello che deve fare.");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 5;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada di rame");
                    strcpy(inventario[i].Descrizione, "Spada di rame, non molto potente ma comunque utile");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 20;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada di ferro");
                    strcpy(inventario[i].Descrizione, "Spada di ferro, di buona qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 30;
                    inventario[i].Durability = 30;
                    inventario[i].Damage = 30;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada d'acciaio");
                    strcpy(inventario[i].Descrizione, "Spada d'acciaio, utilizzata da molti guerrieri");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 40;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 40;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada d'argento");
                    strcpy(inventario[i].Descrizione, "Spada d'argento, una delle migliori armi");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 50;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 50;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada magica [I]");
                    strcpy(inventario[i].Descrizione, "Spada magica, molto potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 60;
                    inventario[i].Durability = 60;
                    inventario[i].Damage = 60;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada magica [II]");
                    strcpy(inventario[i].Descrizione, "Spada magica, di altissima qualita'");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 70;
                    inventario[i].Durability = 70;
                    inventario[i].Damage = 70;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada magica [III]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 80;
                    inventario[i].Durability = 80;
                    inventario[i].Damage = 80;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada magica [IV]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente quasi fra tutte");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 90;
                    inventario[i].Durability = 90;
                    inventario[i].Damage = 90;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
                    strcpy(inventario[i].nome, "Spada magica [V]");
                    strcpy(inventario[i].Descrizione, "Spada magica, la piu' potente fra tutte");
                    inventario[i].Tipo = "Arma";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 100;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
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
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Ascia di legno \n");
        printf("> (2) Ascia di rame \n");
        printf("> (3) Ascia di ferro \n");
        printf("> (4) Ascia d'acciaio \n");
        printf("> (5) Ascia d'argento \n");
        printf("> (6) Ascia magica[I] \n");
        printf("> (7) Ascia magica[II] \n");
        printf("> (8) Ascia magica[III] \n");
        printf("> (9) Ascia magica[IV] \n");
        printf("> (10) Ascia magica[V] \n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d]--~---~---~---+\n", pg->Gold);
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
                    strcpy(inventario[i].nome, "Ascia di legno");
                    strcpy(inventario[i].Descrizione, "Ascia di legno");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 10;
                    inventario[i].Damage = 5;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia di legno!\n");
        Sleep(1000);
        break;
    case 2:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia di rame");
                    strcpy(inventario[i].Descrizione, "Ascia di rame");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 20;
                    inventario[i].Damage = 10;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia di rame!\n");
        Sleep(1000);
        break;
    case 3:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Ascia di ferro");
                strcpy(inventario[i].Descrizione, "Ascia di ferro");
                inventario[i].Tipo = "Ascia";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 30;
                inventario[i].Durability = 30;
                inventario[i].Damage = 15;
                break;
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia di ferro!\n");
        Sleep(1000);
        break;
    case 4:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia d'acciaio");
                    strcpy(inventario[i].Descrizione, "Ascia d'acciaio");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 40;
                    inventario[i].Durability = 40;
                    inventario[i].Damage = 20;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia d'acciaio!\n");
        Sleep(1000);
        break;
    case 5:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia d'argento");
                    strcpy(inventario[i].Descrizione, "Ascia d'argento");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 50;
                    inventario[i].Durability = 50;
                    inventario[i].Damage = 25;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia d'argento!\n");
        Sleep(1000);
        break;
    case 6:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Ascia magica[I]");
                strcpy(inventario[i].Descrizione, "Ascia magica[I]");
                inventario[i].Tipo = "Ascia";
                inventario[i].Rarity = "Rara";
                inventario[i].Value = 100;
                inventario[i].Durability = 100;
                inventario[i].Damage = 50;
                break;
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia magica[I]!\n");
        Sleep(1000);
        break;
    case 7:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[II]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[II]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 200;
                    inventario[i].Durability = 200;
                    inventario[i].Damage = 100;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia magica[II]!\n");
        Sleep(1000);
        break;
    case 8:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Ascia magica[III]");
                strcpy(inventario[i].Descrizione, "Ascia magica[III]");
                inventario[i].Tipo = "Ascia";
                inventario[i].Rarity = "Rara";
                inventario[i].Value = 300;
                inventario[i].Durability = 300;
                inventario[i].Damage = 150;
                break;
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia magica[III]!\n");
        Sleep(1000);
        break;
    case 9:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Ascia magica[IV]");
                strcpy(inventario[i].Descrizione, "Ascia magica[IV]");
                inventario[i].Tipo = "Ascia";
                inventario[i].Rarity = "Rara";
                inventario[i].Value = 400;
                inventario[i].Durability = 400;
                inventario[i].Damage = 200;
                break;
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia magica[IV]!\n");
        Sleep(1000);
        break;
    case 10:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Ascia magica[V]");
                    strcpy(inventario[i].Descrizione, "Ascia magica[V]");
                    inventario[i].Tipo = "Ascia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 500;
                    inventario[i].Durability = 500;
                    inventario[i].Damage = 250;
                    break;
                }
                else if (inventario[i].nome != "vuoto")
                {
                    SetColor(4); // rosso
                    printf("Non hai spazio nell'inventario!\n");
                    Sleep(1000);
                    break;
                }
            }
        }
        SetColor(2); // verde
        printf("Hai comprato l'ascia magica[V]!\n");
        Sleep(1000);
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
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Lancia di legno \n");
        printf("> (2) Lancia di rame \n");
        printf("> (3) Lancia di ferro \n");
        printf("> (4) Lancia d'acciaio \n");
        printf("> (5) Lancia d'argento \n");
        printf("> (6) Lancia magica[I] \n");
        printf("> (7) Lancia magica[II] \n");
        printf("> (8) Lancia magica[III] \n");
        printf("> (9) Lancia magica[IV] \n");
        printf("> (10) Lancia magica[V] \n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d]--~---~---~---+\n", pg->Gold);
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
                    inventario[i].Damage = 10;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia di legno!\n");
        Sleep(1000);
        break;
    case 2:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
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
                    inventario[i].Damage = 20;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia di rame!\n");
        Sleep(1000);
        break;
    case 3:
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
                inventario[i].Damage = 30;
                pg->Gold -= inventario[i].Value;
                break;
            }
        }
        SetColor(2); // verde
        printf("Hai comprato la lancia di ferro!\n");
        Sleep(1000);
        break;
    case 4:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
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
                    inventario[i].Damage = 40;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia d'acciaio!\n");
        Sleep(1000);
        break;
    case 5:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
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
                    inventario[i].Damage = 50;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia d'argento!\n");
        Sleep(1000);
        break;
    case 6:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[I]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 100;
                    inventario[i].Durability = 100;
                    inventario[i].Damage = 100;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia magica[I]!\n");
        Sleep(1000);
        break;
    case 7:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[II]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 200;
                    inventario[i].Durability = 200;
                    inventario[i].Damage = 200;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia magica[II]!\n");
        Sleep(1000);
        break;
    case 8:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[III]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 300;
                    inventario[i].Durability = 300;
                    inventario[i].Damage = 300;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia magica[III]!\n");
        Sleep(1000);
        break;
    case 9:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[IV]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 400;
                    inventario[i].Durability = 400;
                    inventario[i].Damage = 400;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia magica[IV]!\n");
        Sleep(1000);
        break;
    case 10:
        if (pg->Gold >= 10)
        {
            pg->Gold -= 10;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (inventario[i].nome == "vuoto")
                {
                    strcpy(inventario[i].nome, "Lancia magica[V]");
                    strcpy(inventario[i].Descrizione, "Una lancia magica");
                    inventario[i].Tipo = "Lancia";
                    inventario[i].Rarity = "Rara";
                    inventario[i].Value = 500;
                    inventario[i].Durability = 500;
                    inventario[i].Damage = 500;
                    pg->Gold -= inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la lancia magica[V]!\n");
        Sleep(1000);
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
        printf("+---~---~---~[NEGOZIO]~---~---~---+\n");
        printf("> (1) Mazza di legno \n");
        printf("> (2) Mazza di rame \n");
        printf("> (3) Mazza di ferro \n");
        printf("> (4) Mazza d'acciaio \n");
        printf("> (5) Mazza d'argento \n");
        printf("> (6) Mazza magica[I] \n");
        printf("> (7) Mazza magica[II] \n");
        printf("> (8) Mazza magica[III] \n");
        printf("> (9) Mazza magica[IV] \n");
        printf("> (10) Mazza magica[V] \n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza di legno");
                strcpy(inventario[i].Descrizione, "Una mazza di legno");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 10;
                inventario[i].Durability = 10;
                inventario[i].Damage = 1;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza di legno!\n");
        Sleep(1000);
        break;
    case 2:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza di rame");
                strcpy(inventario[i].Descrizione, "Una mazza di rame");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 20;
                inventario[i].Durability = 20;
                inventario[i].Damage = 2;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza di rame!\n");
        Sleep(1000);
        break;
    case 3:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza di ferro");
                strcpy(inventario[i].Descrizione, "Una mazza di ferro");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 30;
                inventario[i].Durability = 30;
                inventario[i].Damage = 3;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza di ferro!\n");
        Sleep(1000);
        break;
    case 4:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza d'acciaio");
                strcpy(inventario[i].Descrizione, "Una mazza d'acciaio");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 40;
                inventario[i].Durability = 40;
                inventario[i].Damage = 4;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza d'acciaio!\n");
        Sleep(1000);
        break;
    case 5:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza d'argento");
                strcpy(inventario[i].Descrizione, "Una mazza d'argento");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 60;
                inventario[i].Durability = 60;
                inventario[i].Damage = 6;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza d'argento!\n");
        Sleep(1000);
        break;
    case 6:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza magica [I]");
                strcpy(inventario[i].Descrizione, "Una mazza magica [I]");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 70;
                inventario[i].Durability = 70;
                inventario[i].Damage = 7;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [I]!\n");
        Sleep(1000);
        break;
    case 7:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza magica [II]");
                strcpy(inventario[i].Descrizione, "Una mazza magica [II]");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 80;
                inventario[i].Durability = 80;
                inventario[i].Damage = 8;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [II]!\n");
        Sleep(1000);
        break;
    case 8:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza magica [III]");
                strcpy(inventario[i].Descrizione, "Una mazza magica [III]");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 90;
                inventario[i].Durability = 90;
                inventario[i].Damage = 9;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [III]!\n");
        Sleep(1000);
        break;
    case 9:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza magica [IV]");
                strcpy(inventario[i].Descrizione, "Una mazza magica [IV]");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 100;
                inventario[i].Durability = 100;
                inventario[i].Damage = 10;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [IV]!\n");
        Sleep(1000);
        break;
    case 10:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Mazza magica [V]");
                strcpy(inventario[i].Descrizione, "Una mazza magica [V]");
                inventario[i].Tipo = "Mazza";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 110;
                inventario[i].Durability = 110;
                inventario[i].Damage = 11;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato la mazza magica [V]!\n");
        Sleep(1000);
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
        printf("> (1) Pugnale di legno \n");
        printf("> (2) Pugnale di rame \n");
        printf("> (3) Pugnale di ferro \n");
        printf("> (4) Pugnale d'acciaio \n");
        printf("> (5) Pugnale d'argento \n");
        printf("> (6) Pugnale magica[I] \n");
        printf("> (7) Pugnale magica[II] \n");
        printf("> (8) Pugnale magica[III] \n");
        printf("> (9) Pugnale magica[IV] \n");
        printf("> (10) Pugnale magica[V] \n");
        printf("> (11) Indietro \n");
        printf("+---~---~---~--[%d]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 11);
    switch (scelta)
    {
    case 1:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale di legno");
                strcpy(inventario[i].Descrizione, "Un pugnale di legno");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 10;
                inventario[i].Durability = 10;
                inventario[i].Damage = 1;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale di legno!\n");
        Sleep(1000);
        break;
    case 2:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale di rame");
                strcpy(inventario[i].Descrizione, "Un pugnale di rame");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 20;
                inventario[i].Durability = 20;
                inventario[i].Damage = 2;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale di rame!\n");
        Sleep(1000);
        break;
    case 3:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale di ferro");
                strcpy(inventario[i].Descrizione, "Un pugnale di ferro");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 30;
                inventario[i].Durability = 30;
                inventario[i].Damage = 3;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale di ferro!\n");
        Sleep(1000);
        break;
    case 4:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale d'acciaio");
                strcpy(inventario[i].Descrizione, "Un pugnale d'acciaio");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 40;
                inventario[i].Durability = 40;
                inventario[i].Damage = 4;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale d'acciaio!\n");
        Sleep(1000);
        break;
    case 5:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale d'argento");
                strcpy(inventario[i].Descrizione, "Un pugnale d'argento");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 50;
                inventario[i].Durability = 50;
                inventario[i].Damage = 5;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale d'argento!\n");
        Sleep(1000);
        break;
    case 6:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale magico [I]");
                strcpy(inventario[i].Descrizione, "Un pugnale magico [I]");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 60;
                inventario[i].Durability = 60;
                inventario[i].Damage = 6;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale magico [I]!\n");
        Sleep(1000);
        break;
    case 7:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale magico [II]");
                strcpy(inventario[i].Descrizione, "Un pugnale magico [II]");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 70;
                inventario[i].Durability = 70;
                inventario[i].Damage = 7;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale magico [II]!\n");
        Sleep(1000);
        break;
    case 8:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale magico [III]");
                strcpy(inventario[i].Descrizione, "Un pugnale magico [III]");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 80;
                inventario[i].Durability = 80;
                inventario[i].Damage = 8;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale magico [III]!\n");
        Sleep(1000);
        break;
    case 9:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale magico [IV]");
                strcpy(inventario[i].Descrizione, "Un pugnale magico [IV]");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 90;
                inventario[i].Durability = 90;
                inventario[i].Damage = 9;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale magico [IV]!\n");
        Sleep(1000);
        break;
    case 10:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "vuoto")
            {
                strcpy(inventario[i].nome, "Pugnale magico [V]");
                strcpy(inventario[i].Descrizione, "Un pugnale magico [V]");
                inventario[i].Tipo = "Pugnale";
                inventario[i].Rarity = "Comune";
                inventario[i].Value = 100;
                inventario[i].Durability = 100;
                inventario[i].Damage = 10;
                pg->Gold = pg->Gold - inventario[i].Value;
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
        SetColor(2); // verde
        printf("Hai comprato un pugnale magico [V]!\n");
        Sleep(1000);
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
        printf("> (1) Arco di legno \n");
        printf("> (2) Arco di rame \n");
        printf("> (3) Arco di ferro \n");
        printf("> (4) Arco d'acciaio \n");
        printf("> (5) Arco d'argento \n");
        printf("> (6) Arco magico[I] \n");
        printf("> (7) Arco magico[II] \n");
        printf("> (8) Arco magico[III] \n");
        printf("> (9) Arco magica[IV] \n");
        printf("> (10) Arco magico[V] \n");
        printf("> (11) Frecce \n");
        printf("> (12) Indietro \n");
        printf("+---~---~---~--[%d]--~---~---~---+\n", pg->Gold);
    } while (scelta < 1 || scelta > 12);
    switch (scelta)
    {
    case 1:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco di legno")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco di legno!\n");
        Sleep(1000);
        break;
    case 2:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco di rame")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco di rame!\n");
        Sleep(1000);
        break;
    case 3:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco di ferro")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco di ferro!\n");
        Sleep(1000);
        break;
    case 4:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco d'acciaio")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco d'acciaio!\n");
        Sleep(1000);
        break;
    case 5:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco d'argento")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco d'argento!\n");
        Sleep(1000);
        break;
    case 6:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco magico [I]")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco magico [I]!\n");
        Sleep(1000);
        break;
    case 7:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco magico [II]")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco magico [II]!\n");
        Sleep(1000);
        break;
    case 8:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco magico [III]")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco magico [III]!\n");
        Sleep(1000);
        break;
    case 9:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco magico [IV]")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco magico [IV]!\n");
        Sleep(1000);
        break;
    case 10:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Arco magico [V]")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Arco magico [V]!\n");
        Sleep(1000);
        break;
    case 11:
        for (int i = 0; i < SIZE_INV; i++)
        {
            if (inventario[i].nome == "Frecce")
            {
                pg->Gold = pg->Gold - inventario[i].Value;
                strcpy(inventario[i].nome, "vuoto");
                strcpy(inventario[i].Descrizione, "vuoto");
                inventario[i].Tipo = "vuoto";
                inventario[i].Rarity = "vuoto";
                inventario[i].Value = 0;
                inventario[i].Durability = 0;
                inventario[i].Damage = 0;
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
        SetColor(2); // verde
        printf("Hai comprato la Frecce!\n");
        Sleep(1000);
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
        printf("> (1) Pozione di vita (I) \n");
        printf("> (2) Pozione di vita (II) \n");
        printf("> (3) Pozione di vita (II) \n");
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
                    strcpy(inventario[i].nome, "Pozione di vita (1)");
                    strcpy(inventario[i].Descrizione, "Ripristina 10 punti vita");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 10;
                    inventario[i].Durability = 1;
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
        if (pg->Gold >= 20)
        {
            pg->Gold = pg->Gold - 20;
            for (int i = 0; i < SIZE_INV; i++)
            {
                if (strcmp(inventario[i].nome, "vuoto") == 0)
                {
                    strcpy(inventario[i].nome, "Pozione di vita (2)");
                    strcpy(inventario[i].Descrizione, "Ripristina 20 punti vita");
                    inventario[i].Tipo = "Pozione";
                    inventario[i].Rarity = "Comune";
                    inventario[i].Value = 20;
                    inventario[i].Durability = 1;
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
        printf("> (1) Pozione di mana (I) \n");
        printf("> (2) Pozione di mana (II) \n");
        printf("> (3) Pozione di mana (III) \n");
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

void negozio(ST *pg, O *inventario, O *equipaggiamento)
{
    int scelta;
    do
    {
        clear();
        setcolor(5); // viola
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
        vendi_oggetti(pg, inventario, equipaggiamento);
        break;
    case 3:
        break;
    default:
        SetColor(4); // rosso
        printf("Scelta non valida!\n");
        Sleep(1000);
    }
}

void zaino(ST *pg, O *inventario, O *equipaggiamento)
{
    print_zaino(inventario);
    
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
    inv_iniziale(inventario);
    equip_iniziale(&pg, equipaggiamento);
    SetColor(2); // verde
    printf("debug riuscito...");
    menu(&pg, inventario, equipaggiamento);
    return 0;
}