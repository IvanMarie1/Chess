#include <stdio.h>
#include <stdlib.h>
#include "echiquier.h"



int main(void) {
    echiquier* ech = creer_echiquier();
    afficher_echiquier(ech);
    liberer_echiquier(ech);
    return 0;
}
