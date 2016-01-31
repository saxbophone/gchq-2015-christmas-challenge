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
        key k[9] = {};
        set s[25] = {};
        row_to_set(PUZZLE, i, s, k);
        set_results results = find_valid_sets(k, s);
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
        key k[9] = {};
        set s[25] = {};
        col_to_set(PUZZLE, i, s, k);
        set_results results = find_valid_sets(k, s);
        printf("%06lu                 |\n", results.count);
        free(results.sets);
    }
    printf("===================================\n\n");
    return 0;
}
