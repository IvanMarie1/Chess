
/// @brief Couple d'entier pour représenter un vecteur
struct vecteur {
    int x;
    int y;
};
typedef struct vecteur vecteur;

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
    vecteur** mouv; // mouvements possibles des pièces
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

/// @brief Libère la mémoire liée à l'échiquier
/// @param e L'échiquier à vider
void liberer_echiquier(echiquier* e);
