#ifndef BOARDSET_H
#define BOARDSET_H

#include <stdbool.h>
#include <stdint.h>

#include "board.h"

union boardset_node {
	union boardset_node *b[2];
	bool l[2];
};

struct boardset {
	uint64_t num_boards;
	union boardset_node *root;
};

typedef struct boardset *boardset_t;

boardset_t new_boardset();
void boardset_add(boardset_t boardset, board_t board);
void boardset_iter(boardset_t boardset, void (*f) (void *, board_t), void *param);
void boardset_free(boardset_t boardset);

#endif
