# This Python implementation is too slow to be useful,
# but it can serve as a cross-check for small numbers
# of jumps.

MOVES = (
	(0, 1, 2),
	(0, 3, 8),
	(1, 4, 9),
	(2, 1, 0),
	(2, 5, 10),
	(3, 4, 5),
	(3, 8, 15),
	(4, 9, 16),
	(5, 4, 3),
	(5, 10, 17),
	(6, 7, 8),
	(6, 13, 20),
	(7, 8, 9),
	(7, 14, 21),
	(8, 3, 0),
	(8, 9, 10),
	(8, 15, 22),
	(8, 7, 6),
	(9, 4, 1),
	(9, 10, 11),
	(9, 16, 23),
	(9, 8, 7),
	(10, 5, 2),
	(10, 11, 12),
	(10, 17, 22),
	(10, 9, 8),
	(11, 18, 25),
	(11, 10, 9),
	(12, 19, 26),
	(12, 11, 10),
	(13, 14, 15),
	(14, 15, 16),
	(15, 8, 3),
	(15, 16, 17),
	(15, 22, 27),
	(15, 14, 13),
	(16, 9, 4),
	(16, 17, 18),
	(16, 23, 28),
	(16, 15, 14),
	(17, 10, 5),
	(17, 18, 19),
	(17, 24, 29),
	(17, 16, 15),
	(18, 17, 16),
	(19, 18, 17),
	(20, 13, 6),
	(20, 21, 22),
	(21, 14, 7),
	(21, 22, 23),
	(22, 15, 8),
	(22, 23, 24),
	(22, 27, 30),
	(22, 21, 20),
	(23, 16, 9),
	(23, 24, 25),
	(23, 28, 31),
	(23, 22, 21),
	(24, 17, 10),
	(24, 25, 26),
	(24, 29, 32),
	(24, 23, 22),
	(25, 18, 11),
	(25, 24, 23),
	(26, 19, 12),
	(26, 25, 24),
	(27, 22, 15),
	(27, 28, 29),
	(28, 23, 16),
	(29, 24, 17),
	(29, 28, 27),
	(30, 27, 22),
	(30, 31, 32),
	(31, 28, 23),
	(32, 29, 24),
	(32, 31, 30)
)

ROTATED = (
	12, 19, 26,
	11, 18, 25,
	2, 5, 10, 17, 24, 29, 32,
	1, 4, 9, 16, 23, 28, 31,
	0, 3, 8, 15, 22, 27, 30,
	7, 14, 21,
	6, 13, 20
)

CROSS = {
	9,
	15, 16, 17,
	23
}


def print_board(board):
	def p(spaces, a, b):
		print(" " * spaces + "".join([
			"*" if i in board else "."
			for i in range(a, b)
		]))

	p(2, 0, 3)
	p(2, 3, 6)
	p(0, 6, 13)
	p(0, 13, 20)
	p(0, 20, 27)
	p(2, 27, 30)
	p(2, 30, 33)
	print("")

def successors(board):
	for (a,b,c) in MOVES:
		if a in board and b in board and c not in board:
			yield frozenset((board - {a, b}) | {c})

def is_symm(board):
	cross_matches = (
		(9 in board) and (16 in board) and (17 in board)
		and (15 not in board) and (23 not in board)
	)
	if not cross_matches: return False

	for i in range(33):
		if i in CROSS: continue
		if (i in board) == (ROTATED[i] in board): return False

	return True

def count_symm(boards):
	n = 0
	for board in boards:
		if is_symm(board): n += 1
	return n

boards = { frozenset(set(xrange(33)) - {16}) }
for move in range(1, 16):
	print("Finding successors for move %d" % (move,))
	next_boards = set()
	for board in boards:
		next_boards.update(successors(board))
	boards = next_boards
	print("Found %d boards after %d jumps" % (len(boards), move))
	print("...%d of them are symmetrical" % (count_symm(boards)))

# for s in boards:
# 	print_board(s)
