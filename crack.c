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

key build_key(set s) {
    // reconstruct a key of a given set, counting the consecutive runs of black squares (non-zero)
    // first, find the index of the first non-zero item
    // initialise blank key to return
    key k = {};
    uint8_t start = 0;
    while(!(s.items[start]) && start < 25) {
        start++;
    }
    // now count consecutive runs and store in result array
    uint8_t result_counter = 0; // points to curent slot in the key
    for(uint8_t i = start; i < 25; i++) {
        if(result_counter > 9-1) {
            // in case result counter goes out of bounds
            return k;
        }
        if(s.items[i]) {
            k.items[result_counter]++;
        } else if(k.items[result_counter]) {
            // move on to next result key
            result_counter++;
        }
    }
    return k;
}

// given a key array and a set, check if the set is valid according to the key array
bool set_valid(key k, set s) {
    // first get the number of non-zero items in the key
    uint8_t key_len = count_non_zero(k.items, 9);
    // get the total of the items in the key
    uint8_t key_sum = sum_array(k.items, key_len);
    // do the same for the set
    uint8_t set_sum = sum_array(s.items, 25);
    // if the sums aren't equal then we know already it's not valid
    if(key_sum != set_sum) {
        return false;
    } else {
        // if they were equal, it's possibly valid, but we need to do more checks
        // construct the key for this set
        key rebuilt_key = build_key(s);
        // compare it with the target key
        for(uint8_t i = 0; i < key_len; i++) {
            if(k.items[i] != rebuilt_key.items[i]) {
                // if any are not equal, return false
                return false;
            }
        }
    }
    // if we got here then it's correct!
    return true;
}

// converts a 25-item set to a 25-bit int (32-bit really)
packed_set set_to_int(set s) {
    packed_set out = 0;
    for(uint8_t i = 0; i < 25; i++) {
        out |= (s.items[i] << i);
    }
    return out;
}

// converts a 25-bit int (32-bit really) to a 25-item set
set int_to_set(packed_set p) {
    set s = {};
    for(uint8_t i = 0; i < 25; i++) {
        s.items[i] = ((p & (1 << i)) >> i);
    }
    return s;
}

// builds the next set after a given set
// (currently k is not used, and the resulting set may not be valid according to set_valid())
// returns the next set as a 25-bit (32-bit really) int (also stores in param n)
key_set next_set(key k, set c) {
    // NOTE: The current implementation is lazy:
    // Treat the array as a 25-bit number and increment it
    // This should be changed at some point for efficiency
    key_set result = {};
    // 32-bit int to store our *25-bit* int
    result.p = set_to_int(c);
    // increment number by 1
    result.p++;
    // convert back to set
    result.s = int_to_set(result.p);
    return result;
}

// converts a row of the grid to a set and retrieves the key for that row
key_set row_to_set(grid g, uint8_t row_index) {
    key_set result = {};
    // copy across the keys
    for(uint8_t i = 0; i < 9; i++) {
        result.k.items[i] = g.row_keys[row_index].items[i];
    }
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        result.s.items[i] = g.squares[row_index][i];
    }
    return result;
}

// converts a column of the grid to a set and retrieves the key for that column
key_set col_to_set(grid g, uint8_t col_index) {
    key_set result = {};
    // copy across the keys
    for(uint8_t i = 0; i < 9; i++) {
        result.k.items[i] = g.col_keys[col_index].items[i];
    }
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        result.s.items[i] = g.squares[i][col_index];
    }
    return result;
}

// converts a set to a given row in the grid
void set_to_row(grid * g, uint8_t row_index, set s) {
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        g->squares[row_index][i] = s.items[i];
    }
}

// converts a set to a given col in the grid
void set_to_col(grid * g, uint8_t col_index, set s) {
    // copy across the set
    for(uint8_t i = 0; i < 25; i++) {
        g->squares[i][col_index] = s.items[i];
    }
}

// finds all the valid combinations for a given key and stores these and their
// count in a set_combos struct (reallocates the struct as needed)
// PLEASE REMEMBER TO free() MEMORY ALLOCATED BY THIS FUNCTION!
set_combos find_valid_sets(key k) {
    // initialise our dynamic array counter - this keeps track of how much we have allocated
    int64_t allocated = 1024;
    set_combos results = {
        .sets = malloc(allocated * sizeof(packed_set)), // allocate memory
        .count = 0, // initialise valid pattern counter
    };
    // initialise a blank set
    set s = {};
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
        key_set latest = next_set(k, s);
        s = latest.s;
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
            results.sets[results.count] = latest.p;
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

// finds all the valid combinations for all the rows and columns in a given grid
grid_combos find_valid_combos(grid g) {
    // initialise grid_combos object used to store results
    grid_combos results = {};
    // fill in results of rows and cols
    for(uint8_t i = 0; i < 25; i++) {
        // do row first
        key_set r = row_to_set(g, i);
        results.rows[i] = find_valid_sets(r.k);
        // now do column
        key_set c = col_to_set(g, i);
        results.cols[i] = find_valid_sets(c.k);
    }
    return results;
}

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

// returns a grid struct which is the predicted solution to the puzzle, based
// on the number of combinations between different row/column combinations for 0
// and 1 - takes a grid_combos struct as sole argument
grid guess_grid(grid_combos g) {
    // create result grid
    grid result = {};
    // iterate over all squares in the grid, and for each one count the number
    // of successful combinations that set that square to 0 and 1 respectively
    for(uint8_t y = 0; y < 25; y++) {
        for(uint8_t x = 0; x < 25; x++) {
            // printf("Guessing square at (%u, %u)\n", x, y);
            uint64_t score[2] = { 0, 0 }; // two score counters, one for 0 and one for 1
            // matrix-iterate over the combos for this squares row and its column
            for(uint64_t r = 0; r < g.rows[y].count; r++) {
                for(uint64_t c = 0; c < g.cols[x].count; c++) {
                    // for each pair of sets, convert to unpacked sets and check
                    // if they hold the same value for this square
                    set row_set = int_to_set(g.rows[y].sets[r]);
                    set col_set = int_to_set(g.cols[x].sets[c]);
                    // compare
                    if(row_set.items[x] == col_set.items[y]) {
                        // increment counter for the square value that matched
                        score[row_set.items[x]]++;
                    }
                }
            }
            if(score[0] > score[1]) {
                result.squares[x][y] = 0;
                printf(" "); // blank space
            } else if(score[1] > score[0]) {
                result.squares[x][y] = 1;
                printf("\u2588"); // print solid block character
            } else {
                printf("?");
            }
            fflush(stdout);
            // printf("Guessed %u\n", result.squares[x][y]);
        }
        printf("\n");
    }
    return result;
}

// frees dynamically allocated memory contained within the pointer arrays of a
// square_pairs struct
void free_square_pairs(square_pairs s) {
    // 3D array of pointers, hence the densely-nested for loop
    for(uint8_t x = 0; x < 25; x++) {
        for(uint8_t y = 0; y < 25; y++) {
            for(uint8_t z = 0; z < 2; z++) {
                if(s.squares[x][y][z].pairs != NULL) {
                    free(s.squares[x][y][z].pairs);
                    s.squares[x][y][z].pairs = NULL;
                }
            }
        }
    }
}

// displays grid as character drawing in console
void display_grid(grid g) {
    for(uint8_t y = 0; y < 25; y++) {
        for(uint8_t x = 0; x < 25; x++) {
            if(g.squares[x][y]) {
                printf("\u2588"); // print solid block character
            } else {
                printf(" "); // print blank space
            }
        }
        printf("\n");
    }
}
