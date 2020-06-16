# Solitaire

This repository contains some code to analyse reachable positions in Solitaire, played on the traditional cross-shaped English board with 33 holes, starting from the position where all but the central hole are filled.

The reason I wrote this is to discover whether there are any reachable 17-peg positions that have a certain sort of symmetry. (Spoiler: there are not.) The `soli` program implements this search.

The same data structures can also easily be used to find out how many reachable positions there are after some number of jumps: this is implemented by the `seq` program.


## Usage

Assuming you have a standard Unix-like development environment, usage should be as simple as

    make soli && ./soli

or

    make seq && ./seq


## Data structures

A board position is represented by a 64-bit unsigned integer, of which only the least-significant 33 bits are used, corresponding to the 33 holes in the board. Sets of boards are represented by a simple binary tree with 33 levels, one for each bit.
