#include <stdio.h>
#include <stdlib.h>



/// @brief Une pièce d'un jeu d'échec
struct piece {
    int id; // identifiant de la pièce (0: pion, 1: cavalier, 2: fou, 3: tour, 4: dame, 5: roi)
    int n_repet; // nombre de fois qu'on peut répéter le mouvement
    int en_vie; // 1 si le pion est en vie
    int joueur; // numero du joueur
};
typedef struct piece piece;

/// @brief Un tableau des cases de l'échiquier contenant des pointeurs vers les pieces
struct echiquier {
    piece*** cases; // cases de l'échiquier
    int*** mouv; // mouvements possibles des pièces
};
typedef struct echiquier echiquier;




/// @brief Convertit une pièce en caractère
/// @param p La pièce à convertir
/// @return Une lettre correspondant à la pièce
char piece_to_char(piece* p);

/// @brief Affiche une ligne d'échiquier 
/// @param i Le numéro de la ligne
/// @param j Le numéro de la colonne
/// @param ech L'échiquier en question
void afficher_case(int i, int j, echiquier* ech);

/// @brief Affiche un échiquier dans la console
/// @param ech L'échiquier à afficher
void afficher_echiquier(echiquier* ech);

/// @brief Créer un échiquier en allouant de la mémoire
/// @return Renvoie un pointeur vers une structure d'échiquier
echiquier* creer_echiquier();

/// @brief Ajoute les mouvements possibles des pièces à l'échiquier
/// @param e L'échiquier qui reçoit le tableau
void creer_mouvements(echiquier* e);

/// @brief Ajoute des pointeurs vers les pièces de l'échiquier
/// @param e L'échiquier qui reçoit les pièces
void creer_cases(echiquier* e);

/// @brief Créer un pointeur vers une pièce
/// @param id Identifiant de la pièce
/// @param i_joueur Identifiant du joueur
/// @param n_repet Nombre de répétition du mouvement
/// @return Pointeur vers la pièce
piece* creer_piece(int id, int i_joueur, int n_repet);






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
    e->mouv = (int***)malloc(6 * sizeof(int**));
    for (int i_piece = 0; i_piece < 6; i_piece++) {
        e->mouv[i_piece] = (int**)malloc(n_mouv[i_piece] * sizeof(int*));
        for (int i_mouv = 0; i_mouv < n_mouv[i_piece]; i_mouv++) {
            e->mouv[i_piece][i_mouv] = (int*)malloc(2 * sizeof(int));
            e->mouv[i_piece][i_mouv][0] = list_mouv[i_piece][i_mouv][0];
            e->mouv[i_piece][i_mouv][1] = list_mouv[i_piece][i_mouv][1];
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




int main(void) {
    echiquier* ech = creer_echiquier();
    afficher_echiquier(ech);
    return 0;
}
