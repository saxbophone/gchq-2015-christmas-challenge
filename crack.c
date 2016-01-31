#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "crack.h"


uint8_t count_non_zero(uint8_t array[], uint8_t len) {
    // count the number of non-zero elements in an array and return it
    uint8_t count = 0;
    for(uint8_t i = 0; i < len; i++) {
        if(array[i]) {
            count++;
        }
    }
    return count;
}

uint8_t sum_array(uint8_t array[], uint8_t len) {
    // returns sum of all items in an array
    uint8_t sum = 0;
    for(uint8_t i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

void build_key(uint8_t array[], uint8_t len, uint8_t result[], uint8_t result_len) {
    // reconstruct a key of a given set, counting the consecutive runs of black squares (non-zero)
    // first, find the index of the first non-zero item
    uint8_t start = 0;
    while(!(array[start]) && start < len) {
        start++;
    }
    // now count consecutive runs and store in result array
    uint8_t result_counter = 0; // points to curent slot in the key
    for(uint8_t i = start; i < len; i++) {
        if(result_counter > result_len-1) {
            // in case result counter goes out of bounds
            return;
        }
        if(array[i]) {
            result[result_counter]++;
        } else if(result[result_counter]) {
            // move on to next result key
            result_counter++;
        }
    }
}

// given a key array and a set, check if the set is valid according to the key array
bool set_valid(key_set check) {
    // first get the number of non-zero items in the key
    uint8_t key_len = count_non_zero(check.k, 9);
    // get the total of the items in the key
    uint8_t key_sum = sum_array(check.k, 9);
    // do the same for the set
    uint8_t set_sum = sum_array(check.s, 25);
    // if the sums aren't equal then we know already it's not valid
    if(key_sum != set_sum) {
        return false;
    } else {
        // if they were equal, it's possibly valid, but we need to do more checks
        // construct the key for this set
        uint8_t rebuilt_key[9] = {};
        build_key(check.s, 25, rebuilt_key, 9);
        // compare it with the target key
        for(uint8_t i = 0; i < 9; i++) {
            if(check.k[i] != rebuilt_key[i]) {
                // if any are not equal, return false
                return false;
            }
        }
    }
    // if we got here then it's correct!
    return true;
}

// builds the first valid possibility for a set's key
void build_set(key k[9], set s[25]) {
    uint8_t m = 0;
    for(uint8_t i = 0; i < 9; i++) {
        for(uint8_t j = 0; j < k[i]; j++) {
            s[m] = 1;
            m++;
        }
        s[m] = 0;
        m++;
    }
}

// converts a 25-item set to a 25-bit int (32-bit really)
packed_set set_to_int(set in[25]) {
    packed_set out = 0;
    for(uint8_t i = 0; i < 25; i++) {
        out |= (in[i] << i);
    }
    return out;
}

// converts a 25-bit int (32-bit really) to a 25-item set
void int_to_set(packed_set in, set out[25]) {
    for(uint8_t i = 0; i < 25; i++) {
        out[i] = ((in & (1 << i)) >> i);
    }
}

// builds the next set after a given set
// (currently k is not used, and the resulting set may not be valid according to set_valid())
// returns the next set as a 25-bit (32-bit really) int (also stores in param n)
packed_set next_set(key k[9], set c[25], set n[25]) {
    // NOTE: The current implementation is lazy:
    // Treat the array as a 25-bit number and increment it
    // This should be changed at some point for efficiency

    // 32-bit int to store our *25-bit* int
    packed_set number = set_to_int(c);
    // increment number by 1
    number++;
    // convert back to set
    int_to_set(number, n);
    return number;
}

// converts a row of the grid to a set and retrieves the key for that row
void row_to_set(grid g, uint8_t row_index, set s[25], key k[9]) {
    // copy across the keys
    for(uint8_t i = 0; i < 9; i++) {
        k[i] = g.row_keys[row_index][i];
    }
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        s[i] = g.squares[row_index][i];
    }
}

// converts a set to a given row in the grid
void set_to_row(grid * g, uint8_t row_index, set s[25]) {
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        g->squares[row_index][i] = s[i];
    }
}

// converts a column of the grid to a set and retrieves the key for that column
void col_to_set(grid g, uint8_t col_index, set s[25], key k[9]) {
    // copy across the keys
    for(uint8_t i = 0; i < 9; i++) {
        k[i] = g.col_keys[col_index][i];
    }
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        s[i] = g.squares[i][col_index];
    }
}

// converts a set to a given col in the grid
void set_to_col(grid * g, uint8_t col_index, set s[25]) {
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        g->squares[i][col_index] = s[i];
    }
}

// finds all the valid combinations for a given set and stores these and their
// count in a set_combos struct (reallocates the struct as needed)
// PLEASE REMEMBER TO free() MEMORY ALLOCATED BY THIS FUNCTION!
set_combos find_valid_sets(key k[9], set s[25]) {
    // initialise our dynamic array counter - this keeps track of how much we have allocated
    int64_t allocated = 1024;
    set_combos results = {
        .sets = malloc(allocated * sizeof(packed_set)), // allocate memory
        .count = 0, // initialise valid pattern counter
    };
    // if malloc failed, abort
    if(results.sets == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        abort();
    }
    if(set_valid(k, s)) {
        // if this first set was valid, then increment counter and store 32-bit int in valid array
        results.sets[results.count] = set_to_int(s);
        results.count++;
    }
    // now iterate the set and store any newly found patterns, re-allocating as needed
    for(uint64_t i = 0; i < 33554432; i++) {
        packed_set latest = next_set(k, s, s);
        if(set_valid(k, s)) {
            // re-allocate dynamic memory if we need to
            if(results.count == allocated) {
                // set next allocation size to current size + 1024
                allocated += 1024;
                // try and re-allocate memory
                results.sets = realloc(results.sets, allocated * sizeof(packed_set));
                // if realloc failed, abort
                if(results.sets == NULL) {
                    fprintf(stderr, "Failed to re-allocate memory.\n");
                    abort();
                }
            }
            // store latest valid result as a 32-bit int
            results.sets[results.count] = latest;
            // increment found counter
            results.count++;
        }
    }
    // finally, resize dynamic array to exactly the number of found items
    results.sets = realloc(results.sets, results.count * sizeof(packed_set));
    // if realloc failed, abort
    if(results.sets == NULL) {
        fprintf(stderr, "Failed to re-allocate memory.\n");
        abort();
    }
    return results;
}

// // finds all the valid combinations for all the rows and columns in a given grid
// grid_combos find_valid_combos(grid g) {
//     // initialise grid_combos object used to store results
//     grid_combos results = {};
//     // fill in results of rows and cols
//     for(uint8_t i = 0; i < 25; i++) {
//         // do row first
//         set row_set[25] = {};
//         key row_key[9] = {};
//         row_to_set(g, i, row_set, row_key);
//         results.rows[i] = find_valid_sets(row_key, row_set);
//         // now do column
//         set col_set[25] = {};
//         key col_key[9] = {};
//         col_to_set(g, i, col_set, col_key);
//         results.cols[i] = find_valid_sets(row_key, row_set);
//     }
// }

// frees dynamically allocated memory contained within the rows and cols of a given grid_combos struct
void free_grid_combos(grid_combos g) {
    // free all rows and cols at same time
    for(uint8_t i = 0; i < 25; i++) {
        if(g.rows[i].sets != NULL) {
            free(g.rows[i].sets);
            g.rows[i].sets = NULL;
        }
        if(g.cols[i].sets != NULL) {
            free(g.cols[i].sets);
            g.cols[i].sets = NULL;
        }
    }
}
