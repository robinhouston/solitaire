#include <stdint.h>
#include <stdlib.h>

#include "boardset.h"

static union boardset_node *alloc_node(bool is_leaf) {
	union boardset_node *node = malloc(sizeof(union boardset_node));
	if (is_leaf) {
		node->l[0] = false;
		node->l[1] = false;
	}
	else {
		node->b[0] = NULL;
		node->b[1] = NULL;
	}

	return node;
}

boardset_t new_boardset() {
	boardset_t boardset = malloc(sizeof(struct boardset));
	boardset->num_boards = 0;
	boardset->root = alloc_node(false);

	return boardset;
}

void boardset_add(boardset_t boardset, board_t board) {
	union boardset_node *node = boardset->root;

	for (int i = 0; i < 32; ++i, board = (board >> 1)) {
		bool b = (board & 1);
		if (!node->b[b]) {
			node->b[b] = alloc_node(i == 31);
		}
		node = node->b[b];
	}

	if (!(node->l[board & 1])) {
		boardset->num_boards++;
		node->l[board & 1] = true;
	}
}

static void iter_node(
	int level, board_t partial,
	union boardset_node *node,
	void (f) (void *, board_t),
	void *param
) {
	if (level == 32) {
		if (node->l[0]) f(param, partial);
		if (node->l[1]) f(param, partial | (1ll << level));
		return;
	}
	if (node->b[0]) {
		iter_node(level + 1, partial, node->b[0], f, param);
	}
	if (node->b[1]) {
		iter_node(level + 1, partial | (1ll << level), node->b[1], f, param);
	}
}

void boardset_iter(boardset_t boardset, void (f) (void *, board_t), void *param) {
	iter_node(0, 0, boardset->root, f, param);
}

static void free_node(int level, union boardset_node *node) {
	if (!node) return;
	if (level != 32) {
		free_node(level + 1, node->b[0]);
		free_node(level + 1, node->b[1]);
	}
	free(node);
}

void boardset_free(boardset_t boardset) {
	free_node(0, boardset->root);
	free(boardset);
}
