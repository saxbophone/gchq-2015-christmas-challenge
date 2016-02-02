#include <stdio.h>

#include "crack.h"

#include "puzzle.inc"


int main(int argc, char const *argv[]) {
    // this tests the function find_valid_combos()
    // this function is not tested in the test suite as it takes quite a long
    // time to run (roughly 7 minutes).
    // find all combinations of all rows and columns:
    printf("Finding valid combinations for rows and columns (7 minutes approx.)\n");
    grid_combos first_round_results = find_valid_combos(PUZZLE);
    printf("Pairing up valid combos between rows and columns for each square in grid.\n");
    square_pairs second_round_results = find_square_combos(first_round_results);
    printf("DONE. Freeing up resources.\n");
    // DON'T FORGET TO FREE THE ALLOCATED MEMORY!
    free_square_pairs(second_round_results);
    free_grid_combos(first_round_results);
    printf("FINISHED.\n");
    return 0;
}
