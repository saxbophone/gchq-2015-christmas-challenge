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
