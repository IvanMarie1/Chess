#include <stdbool.h>


/// @brief Pair of integers to represent a vector
struct vector {
	int x;
	int y;
};
typedef struct vector vector;

/// @brief A chess piece
struct piece {
	int id; // piece's ID (0: pawn, 1: knight, 2: bishop, 3: rook, 4: queen, 5: king)
	int player; // player's number
	int n_moves; // number of different moves possible
	bool can_repeat; // true if the piece can repeat movements
	bool alive; // true if the piece is alive
};
typedef struct piece piece;

/// @brief A 2D-array of chessboard squares containing pointers toward pieces
struct chessboard {
	piece ***squares; // chessboard squares
	vector **moves; // possible movements of pieces
};
typedef struct chessboard chessboard;

/// @brief Convert a piece into a character
/// @param p Piece to convert
/// @return A character corresponding to the piece
char piece_to_char (piece *p);

/// @brief Print a chessboard square
/// @param i Row number
/// @param j Column number
/// @param ech Chessboard to print
void print_square (int i, int j, chessboard *chs);

/// @brief Print a chessboard in the console
/// @param ech Chessboard to print
void print_chessboard (chessboard *chs);

/// @brief Create a chessboard by allocating memory
/// @return Pointer toward a chessboard struct
chessboard *create_chessboard ();

/// @brief Add piece's movements to the chessboard
/// @param chs Chessboard receiving data
void add_movements (chessboard *chs);

/// @brief Add pointers toward chessboard pieces
/// @param chs Chessboard receiving data
void create_squares (chessboard *chs);

/// @brief Create a pointer toward a piece
/// @param id Piece's ID
/// @param i_player Player's number
/// @param n_moves Number of possible moves
/// @param can_repeat true if the piece can repeat a movement
/// @return Pointer toward the piece
piece *create_piece (int id, int i_player, int n_moves, bool can_repeat);

/// @brief Free memory allocated to the chessboard
/// @param chs Chessboard to free
void free_chessboard (chessboard *chs);

/// @brief Convert a board coordinates (eg. d4) into a vector (eg. {3, 3])
/// @param coord Coordinate to convert
/// @return Vector corresponding to the coordinates
vector text_to_vector (char *coord);

/// @brief Determine the possible moves of a piece
/// @param row Current row of the piece
/// @param col Current column of the piece
/// @param chs Chessboard where the piece is located
/// @return An array of vector corresponding to the possible moves
vector *get_moves (int row, int col, chessboard *chs);

/// @brief Move a piece on the chessboard
/// @param start Current position of the piece
/// @param end Target position
/// @param chs Chessboard containing piece
void move_piece (vector start, vector end, chessboard *chs);

/// @brief Play a piece depending on a text instruction
/// @param action String containing the instruction
/// @param chs Chessboard containing pieces
void play_piece (const char *action, chessboard *chs);
