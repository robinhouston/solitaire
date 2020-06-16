#ifndef MOVES_H
#define MOVES_H

#include "boardset.h"

int ROTATED[33];
void moves_init();
boardset_t moves_succ(boardset_t boardset);

#endif
