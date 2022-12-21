#include <stdio.h>
#include <stdlib.h>

struct Personaggio{
    char *name;
    int *lvl;
    int *hp;
    int *armor;

};
typedef struct Personaggio PG;

void scan_information( PG *Persona){

}
int main() {
    PG persona;
    scan_information(&persona);

}