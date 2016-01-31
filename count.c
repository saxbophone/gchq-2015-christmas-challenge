#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "crack.h"

#include "puzzle.inc"


int main(int argc, char const *argv[]) {
    // show the number of possible combinations for each row and column of a grid
    printf("Finding valid settings for all Rows\n");
    printf("===================================\n");
    printf("| Row    | Possible Combinations  |\n");
    printf("===================================\n");
    for(uint8_t i = 0; i < 25; i++) {
        printf("| %02d     | ", i+1);
        fflush(stdout);
        key_set r = row_to_set(PUZZLE, i);
        set_combos results = find_valid_sets(r.k, r.s);
        printf("%06lu                 |\n", results.count);
        free(results.sets);
    }
    printf("===================================\n\n");

    printf("Finding valid settings for all Cols\n");
    printf("===================================\n");
    printf("| Col    | Possible Combinations  |\n");
    printf("===================================\n");
    for(uint8_t i = 0; i < 25; i++) {
        printf("| %02d     | ", i+1);
        fflush(stdout);
        key_set c = col_to_set(PUZZLE, i);
        set_combos results = find_valid_sets(c.k, c.s);
        printf("%06lu                 |\n", results.count);
        free(results.sets);
    }
    printf("===================================\n\n");
    return 0;
}
