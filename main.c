#include "chessboard.h"
#include <stdio.h>

int main (void) {
	chessboard *chs = create_chessboard ();
	print_chessboard (chs);
	printf ("\n");
	char input[1000];
	scanf ("%[^\n]s", input);
	play_piece (input, chs);
	printf ("\n");
	print_chessboard (chs);
	free_chessboard (chs);

	return 0;
}
