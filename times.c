#include <stdlib.h>

#include "crack.h"


int main(int argc, char const *argv[]) {
    // roughly time how long it takes to find all the valid patterns for a row
    key_set r = {
        .k = { 1, 7, 3, 1, 1, 2, 0, 0, 0 },
        .s = { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 },
    };
    set_combos results = find_valid_sets(r.k, r.s);
    free(results.sets);
    return 0;
}
