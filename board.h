#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef uint64_t board_t;

void print_board(board_t board);
bool board_is_symmetrical(board_t board);

#endif
