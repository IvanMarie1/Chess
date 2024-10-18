#include <stdio.h>
#include <stdlib.h>
#include "echiquier.h"


void afficher_case(int i, int j, echiquier* ech) {
    if (ech->cases[i][j] != NULL) {
        printf("%c", piece_to_char(ech->cases[i][j]));
    } else if ((i+j)%2 == 0) {
        printf("#");
    } else {
        printf(" ");
    }
}

char piece_to_char(piece* p) {
    int id_piece = p->id;
    switch (id_piece)
    {
    case 0: return 'P';
    case 1: return 'C';
    case 2: return 'F';
    case 3: return 'T';
    case 4: return 'D';
    case 5: return 'R';
    default: return '?';
    }
}



void afficher_echiquier(echiquier* ech) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            afficher_case(i, j, ech);
        }
        printf("\n");
    } 
}



echiquier* creer_echiquier() {
    echiquier* e = (echiquier*)malloc(sizeof(echiquier));

    e->cases = (piece***)malloc(8 * sizeof(piece**));
    for (int i = 0; i < 8; i++) {
        e->cases[i] = (piece**)malloc(8 * sizeof(piece*));
    }


    creer_cases(e);

    creer_mouvements(e);


    return e;
}


void creer_cases(echiquier* e) {
    // cases vides
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            e->cases[i][j] = NULL;
        }
    }


    for (int i_joueur = 0; i_joueur < 2; i_joueur++) {
        int lig = (i_joueur%2 == 0) ? 0 : 7;

        e->cases[lig][3] = creer_piece(4, i_joueur, 8); // dame
        e->cases[lig][4] = creer_piece(5, i_joueur, 1); // roi

        for (int i_piece = 0; i_piece < 2; i_piece++) {
            e->cases[lig][7 * i_piece] = creer_piece(3, i_joueur, 8); // tour
            e->cases[lig][1 + 5 * i_piece] = creer_piece(1, i_joueur, 1); // cavalier
            e->cases[lig][2 + 3 * i_piece] = creer_piece(2, i_joueur, 8); // fou
        }

        for (int i_pion = 0; i_pion < 8; i_pion++) {
            int lig_pion = (i_joueur%2 == 0) ? 1 : 6;
            e->cases[lig_pion][i_pion] = creer_piece(0, i_joueur, 1); // pion
        }
    }

}


void creer_mouvements(echiquier* e) {
    int n_mouv[6] = {3, 8, 4, 4, 8, 8};

    int list_mouv[6][8][2] = {
        {{1, 0}, {1, 1}, {1, -1}}, // Pion
        {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}}, // Cavalier
        {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}, // Fou
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, // Tour
        {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}, // Dame
        {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}} // Roi
    };

    // Alloue la mémoire pour la struct
    e->mouv = (vecteur**)malloc(6 * sizeof(vecteur*));
    for (int i = 0; i < 6; i++) {
        e->mouv[i] = (vecteur*)malloc(n_mouv[i] * sizeof(vecteur));
        for (int j = 0; j < n_mouv[i]; j++) {
            e->mouv[i][j] = (vecteur){list_mouv[i][j][0], list_mouv[i][j][1]};
        }
    }
}


piece* creer_piece(int id, int i_joueur, int n_repet) {
    piece* ma_piece = (piece*)malloc(sizeof(piece));

    ma_piece->id = id;
    ma_piece->joueur = i_joueur;

    ma_piece->en_vie = 1;
    ma_piece->n_repet = n_repet;

    return ma_piece;
}



void liberer_echiquier(echiquier* e) {
    // libère le tableau des mouvements
    for (int i_piece = 0; i_piece < 6; i_piece++) {
        free(e->mouv[i_piece]);
    }
    free(e->mouv);

    // libère les cases
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e->cases[i][j] != NULL) {
                free(e->cases[i][j]);
            }
        }
        free(e->cases[i]);
    }
    free(e->cases);
    
    free(e);
}


vecteur txt_en_vecteur(char* coord) {
    int i_char = 0;
    while (coord[i_char]!='\0' && i_char < 4) {
        i_char++;
    }
    if (i_char != 2) {
        printf("Pas le bon nombre de caractères\n");
        exit(EXIT_FAILURE);
    }
    if (coord[0] < 'a' || coord[0] > 'h' || coord[1] < '1' || coord[1] > '8') {
        printf("Mauvaises coordonnées\n");
        exit(EXIT_FAILURE);
    }

    return (vecteur){(int)(coord[0]-'a'), (int)(coord[1]-'1')};
}
