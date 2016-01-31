#include <stdio.h>

#include "crack.h"

#include "puzzle.inc"


int main(int argc, char const *argv[]) {
    // this tests the function find_valid_combos()
    // this function is not tested in the test suite as it takes quite a long
    // time to run (roughly 7 minutes).
    // find all combinations of all rows and columns:
    grid_combos results = find_valid_combos(PUZZLE);
    // DON'T FORGET TO FREE THE ALLOCATED MEMORY!
    free_grid_combos(results);
    return 0;
}
