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

void inserimento_nome(ST *pg)
{
    clear();
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
    clear();
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
    pg->Vita_Max = pg->Vita_Max + 25;
    pg->Difesa = pg->Difesa + 5;
    pg->Mana_Max = pg->Mana_Max + 10;
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

void equipaggiamento_oggetti(ST *pg, O *inventario, O *equipaggiamento, int i)
{
    clear();
    print_equipaggiamento(equipaggiamento);
    char scelta[SIZE_SENTENCE] = ("Vuoi equipaggiare questo oggetto? (Y)Si o (N)No\n");
    print_decorate_sentence(scelta);
    SetColor(7); // bianco
    char risposta[SIZE_SENTENCE];
    scanf("%s", risposta);
    if (strcmp(risposta, "Y") == 0 || strcmp(risposta, "y") == 0)
    {
        // equipaggiamento
        if (strcmp(equipaggiamento[i].nome, "Arma") == 0)
        {
            pg->Danno = pg->Danno + equipaggiamento[i].Damage;
        }
        else if (strcmp(equipaggiamento[i].nome, "Scudo") == 0)
        {
            pg->Difesa = pg->Difesa + equipaggiamento[i].Durability;
        }
        else if (strcmp(equipaggiamento[i].nome, "Elmo") == 0)
        {
            pg->Difesa = pg->Difesa + equipaggiamento[i].Durability;
        }
        else if (strcmp(equipaggiamento[i].nome, "Pantaloni") == 0)
        {
            pg->Difesa = pg->Difesa + equipaggiamento[i].Durability;
        }
        else if (strcmp(equipaggiamento[i].nome, "Stivali") == 0)
        {
            pg->Difesa = pg->Difesa + equipaggiamento[i].Durability;
        }
        else
        {
            printf("Non puoi equipaggiare questo oggetto\n");
        }
    }
    else if (strcmp(risposta, "N") == 0 || strcmp(risposta, "n") == 0)
    {
        // non equipaggiare
        printf("Non hai equipaggiato questo oggetto\n");
    }
    else
    {
        printf("Risposta non valida\n");
    }
}

void butta_oggetto(ST *pg, O *inventario, O *equipaggiamento, int i)
{
    clear();
    print_zaino(inventario);
    char scelta[SIZE_SENTENCE] = ("Vuoi buttare questo oggetto? (Y)Si o (N)No\n");
    print_decorate_sentence(scelta);
    SetColor(7); // bianco
    char risposta[SIZE_SENTENCE];
    scanf("%s", risposta);
    if (strcmp(risposta, "Y") == 0 || strcmp(risposta, "y") == 0)
    {
        // buttare oggetto
        strcpy(inventario[i].nome, "vuoto");
        inventario[i].Value = 0;
        inventario[i].Durability = 0;
        inventario[i].Damage = 0;
        SetColor(5); // viola
        printf("Hai buttato: %s\n", inventario[i].nome);
    }
    if (strcmp(risposta, "N") == 0 || strcmp(risposta, "n") == 0)
    {
        SetColor(5); // viola
        printf("Oggetto non buttato\n");
    }
    else
    {
        SetColor(4); // viola
        printf("Risposta non valida\n");
    }
}

void usa_oggetto(ST *pg, O *inventario, O *equipaggiamento, int i)
{
    clear();
    // se l'oggetto è un'arma
    if (strcmp(inventario[i].Tipo, "Arma") == 0)
    {
        equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
    }
    // se l'oggetto è un elmo
    if (strcmp(inventario[i].Tipo, "Elmo") == 0)
    {
        equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
    }
    // se l'oggetto è una corazza
    if (strcmp(inventario[i].Tipo, "Corazza") == 0)
    {
        equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
    }
    // se l'oggetto è un paio di pantaloni
    if (strcmp(inventario[i].Tipo, "Pantaloni") == 0)
    {
        equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
    }
    // se l'oggetto è un paio di stivali
    if (strcmp(inventario[i].Tipo, "Stivali") == 0)
    {
        equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
    }

    // se la pozione è una pozione di vita
    if (strcmp(inventario[i].nome, "Pozione di guarigione") == 0)
    {
        // se il pg ha meno del suo massimo di vita
        if (pg->Vita < pg->Vita_Max)
        {
            pg->Vita = pg->Vita + 10;
            if (pg->Vita > pg->Vita_Max)
            {
                pg->Vita = pg->Vita_Max;
            }
            SetColor(5); // viola
            printf("Hai bevuto la pozione di guardione, ora hai %d punti vita\n", pg->Vita);
            // rimuovo l'oggetto dallo zaino
            strcpy(inventario[i].nome, "vuoto");
            strcpy(inventario[i].Descrizione, "");
            inventario[i].Tipo = "";
            inventario[i].Rarity = "";
            inventario[i].Value = 0;
            inventario[i].Durability = 0;
            inventario[i].Damage = 0;

            inventario[i].Damage = 0;
        }
        else
        {
            SetColor(5); // viola
            printf("Hai gia' la vita al massimo\n");
        }
    }
    // se la pozione è una pozione di mana
    if (strcmp(inventario[i].nome, "Pozione di mana") == 0)
    {
        // se il pg ha meno del suo massimo di mana
        if (pg->Mana < pg->Mana_Max)
        {
            pg->Mana = pg->Mana + 10;
            if (pg->Mana > pg->Mana_Max)
            {
                pg->Mana = pg->Mana_Max;
            }
            SetColor(5); // viola
            printf("Hai bevuto la pozione di mana, ora hai %d punti mana\n", pg->Mana);
            // rimuovo l'oggetto dallo zaino
            strcpy(inventario[i].nome, "vuoto");
            strcpy(inventario[i].Descrizione, "");
            inventario[i].Tipo = "";
            inventario[i].Rarity = "";
            inventario[i].Value = 0;
            inventario[i].Durability = 0;
            inventario[i].Damage = 0;
        }
        else
        {
            SetColor(5); // viola
            printf("Hai gia' il mana al massimo\n");
        }
    }
}

void selezione_oggetto(ST *pg, O *inventario, O *equipaggiamento)
{
    clear();
    print_zaino(inventario);
    SetColor(9); // blu
    char scelta[SIZE_SENTENCE] = ("Inserisci il numero in elenco dell'oggetto selezionato\n");
    print_decorate_sentence(scelta);
    int oggetto;
    SetColor(7); // bianco
    scanf("%d", &oggetto);
    int i;
    // ciclo per trovare l'oggetto selezionato
    for (i = 0; i < SIZE_INV; i++)
    {
        if (strcmp(inventario[i].nome, "vuoto") == 0)
        {
            SetColor(5); // viola
            printf("Oggetto non trovato\n");
            selezione_oggetto(pg, inventario, equipaggiamento);
        }
        if (i == oggetto - 1)
        {
            clear();
            SetColor(5); // viola
            printf("Hai selezionato: %s\n", inventario[i].nome);
            SetColor(9); // blu
            char scelta[SIZE_SENTENCE] = ("Cosa vuoi fare con questo oggetto? (1)Equipaggiarlo, (2)Usarlo, (3)Buttarlo, (4)Tornare indietro\n");
            print_decorate_choices(scelta);
            int scelta_utilizzo;
            SetColor(7); // bianco
            scanf("%d", &scelta_utilizzo);
            switch (scelta_utilizzo)
            {
            case 1:
                equipaggiamento_oggetti(pg, inventario, equipaggiamento, i);
                break;
            case 2:
                usa_oggetto(pg, inventario, equipaggiamento, i);
                break;
            case 3:
                butta_oggetto(pg, inventario, equipaggiamento, i);
                break;
            case 4:
                break;
            default:
                SetColor(5); // viola
                printf("Scelta non valida\n");
                selezione_oggetto(pg, inventario, equipaggiamento);
                break;
            }
        }
    }
}

int zaino(ST *pg, O *inventario, O *equipaggiamento)
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

int main()
{
    ST pg;
    inserimento_nome(&pg);
    statistiche_iniziali(&pg);
    const char *Rarity[] = {"Comune", "Raro", "Epico", "Leggendario"};
    const char *Tipo[] = {"Arma", "Elmo", "Corazza", "Pantaloni", "Stivali", "Scudo", "Guarigione", "Buff", "Debuff", "Veleno"};
    O inventario[SIZE_INV];
    O equipaggiamento[SIZE_EQUIP];
    inv_zaino_iniziale(inventario);
    equip_iniziale(&pg, equipaggiamento);
    zaino(&pg, inventario, equipaggiamento);
    SetColor(2); // verde
    printf("programma riuscito...");
    return 0;
}