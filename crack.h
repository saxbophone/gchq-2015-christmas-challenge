#include <stdbool.h>
#include <stdint.h>


// a key is a number specifying a consecutive number of black squares in a row/col
typedef uint8_t key;
// a square is one shaded or unshaded box in the grid, inside a row or column
typedef uint8_t square;
// a set is a row/col unpacked into a 25-item array for ease of use
typedef uint8_t set;

// used where a set is stored as a 32-bit uint
typedef uint32_t packed_set;

// main struct to represent state of the grid of evil
typedef struct {
    // 25 rows/cols, each having a max of 9 items
    key row_keys[25][9];
    key col_keys[25][9];
    square squares[25][25]; // 25 x 25 squares
} grid;

// struct to store possible sets for a row/column - stores pointer to dynamic array
// and size of array (in items, not bytes)
typedef struct {
    packed_set * sets; // pointer to a dynamically allocated array of packed_sets
    uint64_t count; // count of items in above array
} set_combos;

// struct to store possible sets for all rows and columns of a grid, indexed by row/col index
typedef struct {
    set_combos rows[25]; // 25 rows
    set_combos cols[25]; // 25 cols
} grid_combos;

// convenience struct for passing / returning pairs of corresponding keys and sets
typedef struct {
    set s[25];
    key k[9];
} key_set;

// given a key array and a set, check if the set is valid according to the key array
bool set_valid(key k[9], set s[25]);

// builds the first valid possibility for a set's key
void build_set(key k[9], set s[25]);

// builds the next set after a given set
// (currently k is not used, and the resulting set may not be valid according to set_valid())
// returns the next set as a 25-bit (32-bit really) int (also stores in param n)
packed_set next_set(key k[9], set c[25], set n[25]);

// converts a row of the grid to a set and retrieves the key for that row
void row_to_set(grid g, uint8_t row_index, set s[25], key k[9]);

// converts a set to a given row in the grid
void set_to_row(grid * g, uint8_t row_index, set s[25]);

// converts a column of the grid to a set and retrieves the key for that column
void col_to_set(grid g, uint8_t col_index, set s[25], key k[9]);

// converts a set to a given col in the grid
void set_to_col(grid * g, uint8_t col_index, set s[25]);

// finds all the valid combinations for a given set and stores these and their
// count in a set_combos struct (reallocates the struct as needed)
// PLEASE REMEMBER TO free() MEMORY ALLOCATED BY THIS FUNCTION!
set_combos find_valid_sets(key k[9], set s[25]);

// finds all the valid combinations for all the rows and columns in a given grid
grid_combos find_valid_combos(grid g);

// frees dynamically allocated memory contained within the rows and cols of a given grid_combos struct
void free_grid_combos(grid_combos g);
