#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"


void print_square(int i, int j, chessboard* chs) {
    if (chs->squares[i][j] != NULL) {
        printf("%c", piece_to_char(chs->squares[i][j]));
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



void print_chessboard(chessboard* chs) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            print_square(i, j, chs);
        }
        printf("\n");
    } 
}



chessboard* create_chessboard() {
    chessboard* e = (chessboard*)malloc(sizeof(chessboard));

    e->squares = (piece***)malloc(8 * sizeof(piece**));
    for (int i = 0; i < 8; i++) {
        e->squares[i] = (piece**)malloc(8 * sizeof(piece*));
    }


    create_squares(e);

    add_movements(e);


    return e;
}


void create_squares(chessboard* chs) {
    // empty squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chs->squares[i][j] = NULL;
        }
    }


    for (int i_player = 0; i_player < 2; i_player++) {
        int row = (i_player % 2 == 0) ? 0 : 7;

        chs->squares[row][3] = create_piece(4, i_player, 8); // queen
        chs->squares[row][4] = create_piece(5, i_player, 1); // king

        for (int i_piece = 0; i_piece < 2; i_piece++) {
            chs->squares[row][7 * i_piece] = create_piece(3, i_player, 8); // rook
            chs->squares[row][1 + 5 * i_piece] = create_piece(1, i_player, 1); // knight
            chs->squares[row][2 + 3 * i_piece] = create_piece(2, i_player, 8); // bishop
        }

        for (int i_pawn = 0; i_pawn < 8; i_pawn++) {
            int pawn_row = (i_player % 2 == 0) ? 1 : 6;
            chs->squares[pawn_row][i_pawn] = create_piece(0, i_player, 1); // pawn
        }
    }

}


void add_movements(chessboard* chs) {
    int n_moves[6] = {3, 8, 4, 4, 8, 8};

    int list_moves[6][8][2] = {
        {{1, 0}, {1, 1}, {1, -1}}, // Pawn
        {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}}, // Knight
        {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}, // Bishop
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, // Rook
        {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}, // Queen
        {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}} // King
    };

    // Allocate memory for the struct
    chs->moves = (vector**)malloc(6 * sizeof(vector*));
    for (int i = 0; i < 6; i++) {
        chs->moves[i] = (vector*)malloc(n_moves[i] * sizeof(vector));
        for (int j = 0; j < n_moves[i]; j++) {
            chs->moves[i][j] = (vector){list_moves[i][j][0], list_moves[i][j][1]};
        }
    }
}


piece* create_piece(int id, int i_player, int n_repetition) {
    piece* my_piece = (piece*)malloc(sizeof(piece));

    my_piece->id = id;
    my_piece->player = i_player;

    my_piece->alive = 1;
    my_piece->n_repetition = n_repetition;

    return my_piece;
}



void free_chessboard(chessboard* e) {
    // free movements array
    for (int i_piece = 0; i_piece < 6; i_piece++) {
        free(e->moves[i_piece]);
    }
    free(e->moves);

    // free the squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (e->squares[i][j] != NULL) {
                free(e->squares[i][j]);
            }
        }
        free(e->squares[i]);
    }
    free(e->squares);
    
    free(e);
}


vector txt_to_vector(char* coord) {
    // count the number of characters
    int i_char = 0;
    while (coord[i_char]!='\0' && i_char < 4) {
        i_char++;
    }

    if (i_char != 2) {
        printf("Not the right amount of characters\n");
        exit(EXIT_FAILURE);
    }
    if (coord[0] < 'a' || coord[0] > 'h' || coord[1] < '1' || coord[1] > '8') {
        printf("Wrong coordinates\n");
        exit(EXIT_FAILURE);
    }

    return (vector){(int)(coord[0] - 'a'), (int)(coord[1] - '1')};
}
