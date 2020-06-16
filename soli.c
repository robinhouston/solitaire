#include <stdio.h>

#include "boardset.h"
#include "board.h"
#include "moves.h"

static void print_board_if_symmetrical(void *ignored, board_t board) {
	if (board_is_symmetrical(board)) {
		print_board(board);
	}
}

int main() {
	moves_init();

	boardset_t boardset = new_boardset();
	boardset_add(boardset, 0x1FFFEFFFF);

	for (int i = 1; i <= 15; ++i){
		printf("Computing possible boards after %d jumps...\n", i);

		boardset_t next = moves_succ(boardset);
		boardset_free(boardset);
		boardset = next;

		printf("...found %lld boards\n", boardset->num_boards);
	}

	boardset_iter(boardset, print_board_if_symmetrical, NULL);
}
