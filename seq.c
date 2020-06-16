#include <stdio.h>

#include "moves.h"


int main() {
	init();

	boardset_t boardset = new_boardset();
	boardset_add(boardset, 0x1FFFEFFFF);

	for (int i = 1; i < 33; ++i){
		boardset_t next = succ(boardset);
		boardset_free(boardset);
		boardset = next;

		printf("%d: %lld\n", i, boardset->num_boards);
	}
}
