#include <stdbool.h>
#include <stdint.h>

#include "crack.h"


// evaluates if a grid object is correct, if this returns true then we've WON!
bool check_grid(grid check) {
    // check rows, break on first error
    for(uint8_t ry; ry < 25; ry++) {
        bool looking = false; // if we're currently looking or not
        uint8_t current = 0; // current box in key for this row
        uint8_t count = 0; // current count of consecutive black boxes
        uint8_t total_count = 0; // total count of black squares
        uint8_t expected_total = 0;
        for(uint8_t i; i < 9; i++) {
            expected_total += check.x_keys[ry][i];
        }
        for(uint8_t rx; rx < 25; rx++) {
            if(check.boxes[ry][rx] == 1) {
                // it's not a zero (not white)
                looking = true;
                count++;
                total_count++;
                if(count == check.x_keys[ry][current]) {
                    // we found the right number of consecutive squares!
                    // reset count
                    count = 0;
                    // increment counter
                    current++;
                    // no longer looking
                    looking = false;
                }
            } else if(looking == true) {
                // wah wah! we ran out of black squares
                // fail!
                return false;
            }
        }
        // if total count != expected total then it's incorrect
        if(total_count != expected_total) {
            return false;
        }
    }
    // if all were correct up to now then check columns
    for(uint8_t cx; cx < 25; cx++) {
        bool looking = false; // if we're currently looking or not
        uint8_t current = 0; // current box in key for this row
        uint8_t count = 0; // current count of consecutive black boxes
        uint8_t total_count = 0; // total count of black squares
        uint8_t expected_total = 0;
        for(uint8_t i; i < 9; i++) {
            expected_total += check.y_keys[cx][i];
        }
        for(uint8_t cy; cy < 25; cy++) {
            if(check.boxes[cy][cx] == 1) {
                // it's not a zero (not white)
                looking = true;
                count++;
                total_count++;
                if(count == check.y_keys[cx][current]) {
                    // we found the right number of consecutive squares!
                    // reset count
                    count = 0;
                    // increment counter
                    current++;
                    // no longer looking
                    looking = false;
                }
            } else if(looking == true) {
                // wah wah! we ran out of black squares
                // fail!
                return false;
            }
        }
        // if total count != expected total then it's incorrect
        if(total_count != expected_total) {
            return false;
        }
    }
    return true;
}

// modifies grid by one iteration (converts rows to 25-bit ints and adds 1)
grid iterate_grid(grid in) {
    // convert each row to a 32-bit int
    uint32_t rows[25] = {};
    for(uint8_t y = 0; y < 25; y++) {
        rows[y] = 0;
        for(uint8_t x = 0; x < 25; x++) {
            rows[y] |= (in.boxes[y][x] << x);
        }
    }
    // add 1 to the first row. if it overflows, carry to next
    for(uint8_t y = 0; y < 25; y++) {
        rows[y] = ((rows[y] + 1) % 33554432); // 33554432 = 2 ^ 25
        if(rows[y] != 0) {
            // if it didn't overflow, then break
            break;
        }
    }
    // convert each back to a row of squares
    for(uint8_t y = 0; y < 25; y++) {
        for(uint8_t x = 0; x < 25; x++) {
            in.boxes[y][x] = ((rows[y] & (1 << x)) >> x);
        }
    }
    return in;
}
