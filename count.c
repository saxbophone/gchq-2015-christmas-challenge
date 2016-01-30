#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "crack.h"

#include "puzzle.inc"


int main(int argc, char const *argv[]) {
    // show the number of possible combinations for each row and column of a grid
    printf("Finding valid settings for all Rows\n");
    printf("===================================\n");
    for(uint8_t i = 0; i < 25; i++) {
        printf("======== Row %d: ========\n", i+1);
        key k[9] = {};
        set s[25] = {};
        row_to_set(PUZZLE, i, s, k);
        uint64_t found = 0;
        if(set_valid(k, s)) {
            found++;
        }
        for(uint64_t j = 0; j < 33554432; j++) {
            next_set(k, s, s);
            if(set_valid(k, s)) {
                found++;
            }
        }
        printf("%lu Possible Settings\n", found);
    }
    printf("Finding valid settings for all Cols\n");
    printf("===================================\n");
    for(uint8_t i = 0; i < 25; i++) {
        printf("======== Col %d: ========\n", i+1);
        key k[9] = {};
        set s[25] = {};
        col_to_set(PUZZLE, i, s, k);
        uint64_t found = 0;
        if(set_valid(k, s)) {
            found++;
        }
        for(uint64_t j = 0; j < 33554432; j++) {
            next_set(k, s, s);
            if(set_valid(k, s)) {
                found++;
            }
        }
        printf("%lu Possible Settings\n", found);
    }
    return 0;
}
