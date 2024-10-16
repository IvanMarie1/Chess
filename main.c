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
/// @param ech L'échiquier en question
void afficher_ligne(int i, echiquier* ech);

/// @brief Affiche un échiquier dans la console
/// @param ech L'échiquier à afficher
void afficher_echiquier(echiquier* ech);

/// @brief Créer un échiquier en allouant de la mémoire
/// @return Renvoie un pointeur vers une structure d'échiquier
echiquier* creer_echiquier();

/// @brief Crée un pion en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Renvoie un pointeur vers un pion
piece* creer_pion(int i);

/// @brief Crée un cavalier en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Renvoie un pointeur vers une pièce de cavalier
piece* creer_cavalier(int i);


/// @brief Crée un fou en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Le pointeur vers le fou
piece* creer_fou(int i);

/// @brief Crée une tour en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Le pointeur vers la tour
piece* creer_tour(int i);


/// @brief Crée une dame en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Le pointeur vers la dame
piece* creer_dame(int i);


/// @brief Crée le roi en fonction de son joueur
/// @param i Le numéro du joueur
/// @return Le pointeur vers le roi
piece* creer_roi(int i);

/// @brief Ajoute les mouvements possibles des pièces à l'échiquier
/// @param e L'échiquier qui reçoit le tableau
void initialize_moves(echiquier* e);



void afficher_ligne(int i, echiquier* ech) {
    for (int j = 0; j < 8; j++) {
        if (ech->cases[i][j] != NULL) {
            printf("%c", piece_to_char(ech->cases[i][j]));
        } else if ((i+j)%2 == 0) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("\n");
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
        afficher_ligne(i, ech);
    } 
}



echiquier* creer_echiquier() {
    echiquier* e = (echiquier*)malloc(sizeof(echiquier));

    e->cases = (piece***)malloc(8 * sizeof(piece**));
    for (int i = 0; i < 8; i++) {
        e->cases[i] = (piece**)malloc(8 * sizeof(piece*));
    }

    // on ajoute les pièces

    for (int i_joueur = 0; i_joueur < 2; i_joueur++) {
        int lig = (i_joueur%2 == 0) ? 0 : 7;

        e->cases[lig][3] = creer_dame(i_joueur);
        e->cases[lig][4] = creer_roi(i_joueur);

        for (int i_piece = 0; i_piece < 2; i_piece++) {
            e->cases[lig][7 * i_piece] = creer_tour(i_joueur);
            e->cases[lig][1 + 5 * i_piece] = creer_cavalier(i_joueur);
            e->cases[lig][2 + 3 * i_piece] = creer_fou(i_joueur);

            for (int i_pion = 0; i_pion < 4; i_pion++) {
                int lig_pion = (i_joueur%2 == 0) ? 1 : 6;
                e->cases[lig_pion][i_pion + 4 * i_piece] = creer_pion(i_joueur);
            }
        }
    }
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            e->cases[i][j] = NULL;
        }
    }

    initialize_moves(e);


    return e;
}



void initialize_moves(echiquier* e) {
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



piece* creer_pion(int i) {
    piece* pion = (piece*)malloc(sizeof(piece));

    pion->id = 0;
    pion->n_repet = 1;

    pion->joueur = i;
    pion->en_vie = 1;

    return pion;
}



piece* creer_cavalier(int i) {
    piece* cavalier = (piece*)malloc(sizeof(piece));

    cavalier->id = 1;
    cavalier->n_repet = 1;
    
    cavalier->joueur = i;
    cavalier->en_vie = 1;

    return cavalier;
}



piece* creer_fou(int i) {
    piece* fou = (piece*)malloc(sizeof(piece));

    fou->id = 2;
    fou->n_repet = 8;

    fou->joueur = i;
    fou->en_vie = 1;

    return fou;
}



piece* creer_tour(int i) {
    piece* tour = (piece*)malloc(sizeof(piece));

    tour->id = 3;
    tour->n_repet = 8;
    tour->joueur = i;
    tour->en_vie = 1;

    return tour;
}



piece* creer_dame(int i) {
    piece* dame = (piece*)malloc(sizeof(piece));

    dame->id = 4;
    dame->n_repet = 8;
    dame->joueur = i;
    dame->en_vie = 1;

    return dame;
}



piece* creer_roi(int i) {
    piece* roi = (piece*)malloc(sizeof(piece));

    roi->id = 5;
    roi->n_repet = 1;
    roi->joueur = i;
    roi->en_vie = 1;

    return roi;
}



int main(void) {
    echiquier* ech = creer_echiquier();
    afficher_echiquier(ech);
    return 0;
}
