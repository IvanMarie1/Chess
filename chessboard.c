#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chessboard.h"

void print_square (int i, int j, chessboard *chs) {
	// square is not empty
	if (chs->squares[i][j] != NULL) {
		printf ("%c", piece_to_char (chs->squares[i][j]));
	}
		// color one square in two
	else if ((i + j) % 2 == 0) {
		printf ("#");
	}
	else {
		printf (" ");
	}
}

char piece_to_char (piece *p) {
	int id_piece = p->id;
	switch (id_piece) {
	case 0:return 'P';
	case 1:return 'N';
	case 2:return 'B';
	case 3:return 'R';
	case 4:return 'Q';
	case 5:return 'K';
	default:return '?';
	}
}

void print_chessboard (chessboard *chs) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			print_square (i, j, chs);
		}
		printf ("\n");
	}
}

chessboard *create_chessboard () {
	// allocate memory
	chessboard *e = (chessboard *)malloc (sizeof (chessboard));

	e->squares = (piece ***)malloc (8 * sizeof (piece **));
	for (int i = 0; i < 8; i++) {
		e->squares[i] = (piece **)malloc (8 * sizeof (piece *));
	}

	create_squares (e);

	add_movements (e);

	return e;
}

void create_squares (chessboard *chs) {
	// empty squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chs->squares[i][j] = NULL;
		}
	}

	for (int i_player = 0; i_player < 2; i_player++) {
		int row = (i_player % 2 == 0) ? 0 : 7;

		chs->squares[row][3] = create_piece (4, i_player, 8, true); // queen
		chs->squares[row][4] = create_piece (5, i_player, 8, false); // king

		for (int i_piece = 0; i_piece < 2; i_piece++) {
			chs->squares[row][7 * i_piece] = create_piece (3, i_player, 4, false); // rook
			chs->squares[row][1 + 5 * i_piece] = create_piece (1, i_player, 8, false); // knight
			chs->squares[row][2 + 3 * i_piece] = create_piece (2, i_player, 4, true); // bishop
		}

		for (int i_pawn = 0; i_pawn < 8; i_pawn++) {
			int pawn_row = (i_player % 2 == 0) ? 1 : 6;
			chs->squares[pawn_row][i_pawn] = create_piece (0, i_player, 4, false); // pawn
		}
	}

}

void add_movements (chessboard *chs) {
	int n_moves[6] = {4, 8, 4, 4, 8, 8};

	int list_moves[6][8][2] = {
		{{0, 1}, {0, 2}, {1, 1}, {1, -1}}, // Pawn
		{{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}}, // Knight
		{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}, // Bishop
		{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, // Rook
		{{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}, // Queen
		{{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}} // King
	};

	// Allocate memory for the struct
	chs->moves = (vector **)malloc (6 * sizeof (vector *));
	for (int i = 0; i < 6; i++) {
		chs->moves[i] = (vector *)malloc (n_moves[i] * sizeof (vector));
		for (int j = 0; j < n_moves[i]; j++) {
			chs->moves[i][j] = (vector){list_moves[i][j][0], list_moves[i][j][1]};
		}
	}
}

piece *create_piece (int id, int i_player, int n_moves, bool can_repeat) {
	piece *my_piece = (piece *)malloc (sizeof (piece));

	my_piece->id = id;
	my_piece->player = i_player;

	my_piece->can_repeat = can_repeat;
	my_piece->n_moves = n_moves;

	return my_piece;
}

void free_chessboard (chessboard *chs) {
	// free movements array
	for (int i_piece = 0; i_piece < 6; i_piece++) {
		free (chs->moves[i_piece]);
	}
	free (chs->moves);

	// free the squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (chs->squares[i][j] != NULL) {
				free (chs->squares[i][j]);
			}
		}
		free (chs->squares[i]);
	}
	free (chs->squares);

	free (chs);
}

vector text_to_vector (char *coord) {
	// count the number of characters
	int i_char = 0;
	while (coord[i_char] != '\0' && i_char < 4) {
		i_char++;
	}

	if (i_char != 2) {
		printf ("Not the right amount of characters\n");
		exit (EXIT_FAILURE);
	}
	// check the coordinates
	if (coord[0] < 'a' || coord[0] > 'h' || coord[1] < '1' || coord[1] > '8') {
		printf ("Wrong coordinates\n");
		exit (EXIT_FAILURE);
	}

	return (vector){(int)(coord[0] - 'a'), (int)(coord[1] - '1')};
}

vector *get_moves (vector pos, chessboard *chs) {
	// todo different rules for pawns
	// todo free the malloc
	piece *p = chs->squares[pos.y][pos.x];

	vector *legal_moves = chs->moves[p->id];
	vector *possible_moves = (vector *)malloc (65 * sizeof (vector));

	int count = 0;
	for (int i_move = 0; i_move < p->n_moves; i_move++) {
		vector move = legal_moves[i_move];
		int n_repetitions = (p->can_repeat) ? 8 : 1;
		bool condition = true;
		for (int k = 1; k <= n_repetitions && condition; k++) {
			vector new_pos = {pos.x + k * move.x, pos.y + k * move.y};
			// outside the chessboard
			if (new_pos.x < 0 || new_pos.x >= 8 || new_pos.y < 0 || new_pos.y >= 8) {
				condition = false;
				continue;
			}

			piece *target = chs->squares[new_pos.y][new_pos.x];
			if (target == NULL || target->player != p->player) {
				possible_moves[count] = move;
				count++;
			}
			else {
				condition = false;
			}
		}
	}
	possible_moves[count] = (vector){0, 0};
	return possible_moves;
}

void move_piece (vector start, vector end, chessboard *chs) {
	vector move = {end.x - start.x, end.y - start.y};
	if (!is_move_legal (start, move, chs)) {
		printf ("(%d %d) is not a legal move\n", move.x, move.y);
		return;
	}
	chs->squares[end.y][end.x] = chs->squares[start.y][start.x];
	chs->squares[start.y][start.x] = NULL;
}

void play_piece (const char *action, chessboard *chs) {
	int i1, i2;
	char pos1[3], pos2[3];
	for (i1 = 0; action[i1] != ' ' && i1 < 3; i1++) {
		if (i1 == 2 || action[i1] == '\0') {
			exit (EXIT_FAILURE);
		}
		pos1[i1] = action[i1];
	}
	pos1[i1] = '\0';
	for (i2 = 0; action[i1 + i2 + 1] != '\0' && i2 < 3; i2++) {
		if (i2 == 2) {
			exit (EXIT_FAILURE);
		}
		pos2[i2] = action[i1 + i2 + 1];
	}
	pos2[i2] = '\0';
	vector start = text_to_vector (pos1);
	vector end = text_to_vector (pos2);
	move_piece (start, end, chs);
}

bool is_move_legal (vector pos, vector move, chessboard *chs) {
	piece *p = chs->squares[pos.y][pos.x];
	// wrong piece coordinate
	if (p == NULL) {
		return false;
	}

	vector *legal_moves = get_moves (pos, chs);
	for (int i = 0; i < 65; i++) {
		// all possible moves were checked
		if (legal_moves[i].x == 0 && legal_moves[i].y == 0) {
			return false;
		}

		if (legal_moves[i].x == move.x && legal_moves[i].y == move.y) {
			return true;
		}
	}
	return false;
}
