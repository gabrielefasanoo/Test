#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <math.h>
#define SIZE_INV 21
#define SIZE_NOME_OGGETTO 20
#define SIZE_DESCRIZIONE 500

typedef struct Oggetto
{
    char nome[20];
    char Descrizione[500];
    char *Tipo;
    const char *Rarity;
    int Value;
    int Durability;
    int Damage;

} O;

int inv_zaino_iniziale(O *inventario)
{
    int i;
    for (i = 0; i < SIZE_INV; i++)
    {
        switch (i)
        {
        case 0:
            strcpy(inventario[i].nome, "Pozione di guarigine");
            strcpy(inventario[i].Descrizione, "Pozione che guarisce 10 punti vita");
            inventario[i].Tipo = "Guarigione";
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

int zaino(O *inventario)
{
    char lvl_zaino = 'I';
    printf("+---~---~---~ZAINO~---~---~---+\n");
    // stampare la lista degli oggetti presenti nel zaino
    int i;
    for (i = 0; i < SIZE_INV; i++)
    {
        // stampa nome oggetto
        printf("> %s\n", inventario[i].nome);
    }
    printf("+---~---~---~[ %s ]~---~---~---+\n", lvl_zaino);
}

int main() {
    O inventario[SIZE_INV];
    const char *Rarity[] = {"Comune", "Raro", "Epico", "Leggendario"};
    const char *Tipo[] = {"Arma", "Armatura", "Guarigione", "Buff", "Debuff", "Veleno"};
    inv_zaino_iniziale(inventario);
    zaino(inventario);
}