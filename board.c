#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "moves.h"

static char c(board_t board, int i) {
	if ((board & (1ll << i)) != 0) return '*';
	else return '.';
}

void print_board(board_t board) {
	printf("  %c%c%c  \n", c(board, 0), c(board, 1), c(board, 2));
	printf("  %c%c%c  \n", c(board, 3), c(board, 4), c(board, 5));
	printf("%c%c%c%c%c%c%c\n",
		c(board, 6), c(board, 7), c(board, 8),
		c(board, 9),
		c(board, 10), c(board, 11), c(board, 12)
	);
	printf("%c%c%c%c%c%c%c\n",
		c(board, 13), c(board, 14), c(board, 15),
		c(board, 16),
		c(board, 17), c(board, 18), c(board, 19)
	);
	printf("%c%c%c%c%c%c%c\n",
		c(board, 20), c(board, 21), c(board, 22),
		c(board, 23),
		c(board, 24), c(board, 25), c(board, 26)
	);
	printf("  %c%c%c  \n", c(board, 27), c(board, 28), c(board, 29));
	printf("  %c%c%c  \n", c(board, 30), c(board, 31), c(board, 32));
	printf("\n");
}

#define ELL ((1ll << 9) | (1ll << 16) | (1ll << 17))
#define CO_ELL ((1ll << 15) | (1ll << 23))

bool board_is_symmetrical(board_t board) {
	if (!((board & ELL) == ELL && ((~board) & CO_ELL) == CO_ELL)) return false;

	for (int p = 0; p < 33; ++p) {
		switch(p) {
			case 9: case 15: case 16: case 17: case 23:
				continue;
		}

		if (
			((board & (1ll << p)) != 0)
			==
			((board & (1ll << ROTATED[p])) != 0)
		) {
			return false;
		}
	}

	return true;
}
