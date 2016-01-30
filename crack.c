#include <stdbool.h>
#include <stdint.h>

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
bool set_valid(key k[9], set s[25]) {
    // first get the number of non-zero items in the key
    uint8_t key_len = count_non_zero(k, 9);
    // get the total of the items in the key
    uint8_t key_sum = sum_array(k, 9);
    // do the same for the set
    uint8_t set_sum = sum_array(s, 25);
    // if the sums aren't equal then we know already it's not valid
    if(key_sum != set_sum) {
        return false;
    } else {
        // if they were equal, it's possibly valid, but we need to do more checks
        // construct the key for this set
        uint8_t rebuilt_key[9] = {};
        build_key(s, 25, rebuilt_key, 9);
        // compare it with the target key
        for(uint8_t i = 0; i < 9; i++) {
            if(k[i] != rebuilt_key[i]) {
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
uint32_t set_to_int(set in[25]) {
    uint32_t out = 0;
    for(uint8_t i = 0; i < 25; i++) {
        out |= (in[i] << i);
    }
    return out;
}

// converts a 25-bit int (32-bit really) to a 25-item set
void int_to_set(uint32_t in, set out[25]) {
    for(uint8_t i = 0; i < 25; i++) {
        out[i] = ((in & (1 << i)) >> i);
    }
}

// builds the next set after a given set
// (currently k is not used, and the resulting set may not be valid according to set_valid())
// returns the next set as a 25-bit (32-bit really) int (also stores in param n)
uint32_t next_set(key k[9], set c[25], set n[25]) {
    // NOTE: The current implementation is lazy:
    // Treat the array as a 25-bit number and increment it
    // This should be changed at some point for efficiency

    // 32-bit int to store our *25-bit* int
    uint32_t number = set_to_int(c);
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
