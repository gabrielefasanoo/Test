#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RIGHE 24
#define SIZEA 24
#define COLONNE SIZEA * 2 + 1

int main(void)
{
    srand(time(NULL));
    int Asterischi[SIZEA] = {0};
    int ultRig = RIGHE - 1, ultCol = COLONNE - 1, rigxChar = RIGHE - 2;
    printf("Inserisci il punto \" . \" per terminare la richiesta dei dati o \n");
    for (int i = 0; i < SIZEA; i++)
    {
        printf("Inserisci il %i' dato: ", i + 1);
        scanf("%i", &Asterischi[i]);
    }

    // assegnazione automatica dei valori da uno a SIZEA

    /*for (int assegnazione = 0; assegnazione < SIZEA; assegnazione++)
    {
        Asterischi[assegnazione] = assegnazione + 1;
    }*/

    // assegnazione automatica dei valori randomica

    /*for (int assegnazione = 0; assegnazione < SIZEA; assegnazione++)
    {
        Asterischi[assegnazione] = rand() % (RIGHE - 1) + 1;
    }*/

    // creazione del grafico di base
    printf("\n");
    char grafico[RIGHE][COLONNE];

    // inizializzazione di grafico con uno ' ' (spazio)
    for (int i = 0; i < RIGHE; i++)
    {
        for (int o = 0; o < COLONNE; o++)
        {
            grafico[i][o] = ' ';
        }
    }

    for (int i = 0; i < RIGHE; i++)
    {
        for (int o = 0; o < COLONNE; o++)
        {
            if (i == 0 && o == 0) // se ci troviamo nell'angolo in alto
            {
                grafico[i][o] = '^'; // stampa ^
            }
            else if (i == ultRig && o == ultCol) // se ci troviamo all'ultima riga e all'ultima colonna
            {
                grafico[i][o] = '>'; // stampa >
            }
            else if (i == ultRig && o > 0) // se ci troviamo all'ultima riga dopo la prima colonna
            {
                grafico[i][o] = '-'; // stampa -
            }
            else if (o == 0 && i < ultRig) // se ci troviamo alla prima colonna e prima dell'ultima riga
            {
                grafico[i][o] = '|'; // stampa |
            }
            else if (o == 0 && i == ultRig) // se ci troviamo alla prima colonna e all'ultima riga
            {
                grafico[i][o] = '+'; // stampa +
            }
            // printf("%2c", grafico[i][o]);  // stampa del grafico senza Asterischi
        }
        // printf("\n"); //stampa delle righe del grafico
    }

    printf("\n\n\n");

    // posizionamento dell'array di Asterischi sul grafico

    for (int i = 0; i < ultRig; i++)
    {
        for (int o = 1; o < ultCol; o += 2)
        {
            if (i > rigxChar - Asterischi[o / 2])
            {
                grafico[i][o] = '*';
            }
        }
    }

    // stampa del grafico completo
    for (int i = 0; i < RIGHE; i++)
    {
        for (int o = 0; o < COLONNE; o++)
        {
            printf("%2c", grafico[i][o]);
        }
        printf("\n");
    }

    // stampa dei dati dell'array di Asterischi sotto il grafico

    for (int scritte = 0; scritte < SIZEA; scritte++)
    {
        printf("%4i", Asterischi[scritte]);
    }
} // Domenico de Dato