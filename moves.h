#include "boardset.h"

static int MOVES[76 * 3] = {
	0, 1, 2,
	0, 3, 8,
	1, 4, 9,
	2, 1, 0,
	2, 5, 10,
	3, 4, 5,
	3, 8, 15,
	4, 9, 16,
	5, 4, 3,
	5, 10, 17,
	6, 7, 8,
	6, 13, 20,
	7, 8, 9,
	7, 14, 21,
	8, 3, 0,
	8, 9, 10,
	8, 15, 22,
	8, 7, 6,
	9, 4, 1,
	9, 10, 11,
	9, 16, 23,
	9, 8, 7,
	10, 5, 2,
	10, 11, 12,
	10, 17, 22,
	10, 9, 8,
	11, 18, 25,
	11, 10, 9,
	12, 19, 26,
	12, 11, 10,
	13, 14, 15,
	14, 15, 16,
	15, 8, 3,
	15, 16, 17,
	15, 22, 27,
	15, 14, 13,
	16, 9, 4,
	16, 17, 18,
	16, 23, 28,
	16, 15, 14,
	17, 10, 5,
	17, 18, 19,
	17, 24, 29,
	17, 16, 15,
	18, 17, 16,
	19, 18, 17,
	20, 13, 6,
	20, 21, 22,
	21, 14, 7,
	21, 22, 23,
	22, 15, 8,
	22, 23, 24,
	22, 27, 30,
	22, 21, 20,
	23, 16, 9,
	23, 24, 25,
	23, 28, 31,
	23, 22, 21,
	24, 17, 10,
	24, 25, 26,
	24, 29, 32,
	24, 23, 22,
	25, 18, 11,
	25, 24, 23,
	26, 19, 12,
	26, 25, 24,
	27, 22, 15,
	27, 28, 29,
	28, 23, 16,
	29, 24, 17,
	29, 28, 27,
	30, 27, 22,
	30, 31, 32,
	31, 28, 23,
	32, 29, 24,
	32, 31, 30
};

static int ROTATED[33] = {
	12, 19, 26,
	11, 18, 25,
	2, 5, 10, 17, 24, 29, 32,
	1, 4, 9, 16, 23, 28, 31,
	0, 3, 8, 15, 22, 27, 30,
	7, 14, 21,
	6, 13, 20
};

static board_t MOVES_FROM[76];
static board_t MOVES_TO[76];

static void init() {
	for (int i = 0; i < 76; ++i) {
		int a = MOVES[i * 3 + 0];
		int b = MOVES[i * 3 + 1];
		int c = MOVES[i * 3 + 2];

		MOVES_FROM[i] = (1ll << a) | (1ll << b);
		MOVES_TO[i] = (1ll << c);
	}
}

static void add_successors(void *boardset_v, board_t board) {
	boardset_t boardset = (boardset_t) boardset_v;

	for (int i = 0; i < 76; ++i) {
		if (((board & MOVES_FROM[i]) == MOVES_FROM[i])
		&& ((~board) & MOVES_TO[i]) == MOVES_TO[i])
		{
			boardset_add(boardset, board ^ (MOVES_FROM[i] | MOVES_TO[i]));
		}
	}
}

static boardset_t succ(boardset_t boardset) {
	boardset_t next = new_boardset();
	boardset_iter(boardset, add_successors, next);

	return next;
}
