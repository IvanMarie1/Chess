#include <stdio.h>



/// @brief Une pièce d'un jeu d'échec
struct piece {
    int x; // colonne de la pièce
    int y; // ligne de la pièce
    int** mv; // mouvements possibles
    int n_repet; // nombre de fois qu'on peut répéter le mouvement
    int en_vie; // 1 si le pion est en vie
    int joueur; // numero du joueur
    char nom[10]; // nom de la pièce
};
typedef struct piece piece;



/// @brief Un tableau contenant des pièces d'echecs
struct echiquier {
    piece** pieces; // pièces de l'échiquier
};
typedef struct echiquier echiquier;



/// @brief Affiche une ligne d'échiquier 
/// @param i Le numéro de la ligne
/// @param ech L'échiquier en question
void afficher_ligne(int i, echiquier* ech) {
    for (int j = 0; j < 8; j++) {
        if ((i+j)%2 == 0) {
            printf("###");
        } else {
            printf("   ");
        }
    }
    printf("\n");
}



/// @brief Affiche un échiquier dans la console
/// @param ech L'échiquier à afficher
void afficher_echiquier(echiquier* ech) {
    for (int i = 0; i < 8; i++) {
        afficher_ligne(i, ech);
    } 
}



/// @brief Créer un échiquier en allouant de la mémoire
/// @return Renvoie un pointeur vers une structure d'échiquier
echiquier* creer_echiquier() {
    echiquier* e = (echiquier*)malloc(sizeof(echiquier));
    e->pieces = (piece**)malloc(32 * sizeof(piece*));
    // on ajoute les pièces
    for (int i = 0; i<16; i++) {
        e->pieces[i] = creer_pion(i);
    }

    return e;
}



/// @brief Crée un pion en fonction de sa position et son joueur
/// @param i Le numéro du pion
/// @return Renvoie un pointeur vers un pion
piece* creer_pion(int i) {
    piece* pion = (piece*)malloc(sizeof(piece));

    pion->mv = (int**)malloc(3*sizeof(int*));
    for (int i = 0; i < 3; i++) {
        pion->mv[i] = (int*)malloc(2*sizeof(int));
    }
    int direction = (i % 2 == 0) ? -1 : 1;
    pion->mv[0][0] = direction, pion->mv[0][1] = 0;
    pion->mv[1][0] = direction, pion->mv[1][1] = -1;
    pion->mv[2][0] = direction, pion->mv[2][1] = 1;

    pion->n_repet = 1;

    pion->x = i / 2;
    pion->y = (i % 2 == 0) ? 1 : 6;

    pion->joueur = (i % 2 == 0) ? 0 : 1;
    pion->en_vie = 1;

    return pion;
}



/// @brief Crée un cavalier en fonction de sa position et son joueur
/// @param i Le numéro du cavalier
/// @return Renvoie un pointeur vers une pièce de cavalier
piece* creer_cavalier(int i) {
    piece* cavalier = (piece*)malloc(sizeof(piece));

    cavalier->mv = (int**)malloc(8 * sizeof(int*));
    int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int j = 0; j < 8; j++) {
        cavalier->mv[j] = (int*)malloc(2 * sizeof(int));
        cavalier->mv[j][0] = moves[j][0];
        cavalier->mv[j][1] = moves[j][1];   
    }

    cavalier->n_repet = 1;

    cavalier->x = 1 + 5* i/2;
    cavalier->y = i%2 == 0 ? 0 : 7;
    
    cavalier->joueur = i%2 == 0 ? 0 : 1;
    cavalier->en_vie = 1;

    return cavalier;
}



int main(void) {
    echiquier* ech = creer_echiquier();
    afficher_echiquier(ech);
    return 0;
}
