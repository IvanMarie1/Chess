#include "chessboard.h"
#include <stdio.h>

int main (void) {
	chessboard *chs = create_chessboard ();
	print_chessboard (chs);
	char input[1000];
	scanf ("%[^\n]s", input);
	play_piece (input, chs);
	print_chessboard (chs);
	free_chessboard (chs);

	return 0;
}
