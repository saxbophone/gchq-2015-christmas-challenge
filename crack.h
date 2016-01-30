#include <stdbool.h>
#include <stdint.h>


// a key is a number specifying a consecutive number of black squares in a row/col
typedef uint8_t key;
// a square is one shaded or unshaded box in the grid, inside a row or column
typedef uint8_t square;
// a set is a row/col unpacked into a 25-item array for ease of use
typedef uint8_t set;

// main struct to represent state of the grid of evil
typedef struct {
    // 25 rows/cols, each having a max of 9 items
    key row_keys[25][9];
    key col_keys[25][9];
    square squares[25][25]; // 25 x 25 squares
} grid;

// given a key array and a set, check if the set is valid according to the key array
bool set_valid(key k[9], set s[25]);
