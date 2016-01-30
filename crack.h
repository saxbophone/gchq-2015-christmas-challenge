#include <stdint.h>


typedef struct {
    uint8_t boxes[25][25];
    // there are 25 keys for each axis, each could have up to 9 items in it
    uint8_t x_keys[25][9];
    uint8_t y_keys[25][9];
} grid;

// evaluates if a grid object is correct, if this returns true then we've WON!
bool check_grid(grid check);

// modifies grid by one iteration (converts rows to 25-bit ints and adds 1)
grid iterate_grid(grid in);
