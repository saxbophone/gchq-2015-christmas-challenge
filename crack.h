#include <stdbool.h>
#include <stdint.h>


// a key is an array specifying a consecutive number of black squares in a row/col
typedef struct {
    uint8_t items[9];
} key;

// a set is an array representing a row/col unpacked into 25 items for ease of use
typedef struct {
    uint8_t items[25];
} set;

// TODO: Convert this to a 2D array inside a struct type as with key and set
// a square is one shaded or unshaded box in the grid, inside a row or column
typedef uint8_t square;

// used where a set is stored as a 32-bit uint
typedef uint32_t packed_set;

// main struct to represent state of the grid of evil
typedef struct {
    // 25 rows/cols, each having a max of 9 items
    key row_keys[25];
    key col_keys[25];
    square squares[25][25]; // 25 x 25 squares
} grid;

// struct to store possible sets for a row/column - stores pointer to dynamic array
// and size of array (in items, not bytes)
typedef struct {
    packed_set * sets; // pointer to a dynamically allocated array of packed_sets
    uint64_t count; // count of items in above array
} set_combos;

// struct to store one pair of pointers to packed_sets - one row and one column
typedef struct {
    packed_set * row; // points to one row packed_set
    packed_set * col; // points to one col packed_set
} set_pair;

// struct to store a dynamically allocated array of set_pair structs, and the count of them
typedef struct {
    set_pair * pairs; // a dynamic array of set pairs
    uint64_t count; // the number of items in the above array
} set_pair_list;

// struct to store set_pairs of matching sets for each square in the grid
typedef struct {
    // for each square in the 25x25 grid, organised by sets that set that square
    // to 0 and others that set it to 1, a set_pair_list struct
    set_pair_list squares[25][25][2];
} square_pairs;

// struct to store possible sets for all rows and columns of a grid, indexed by row/col index
typedef struct {
    set_combos rows[25]; // 25 rows
    set_combos cols[25]; // 25 cols
} grid_combos;

// convenience struct for passing / returning trios of corresponding keys, sets and packed sets
typedef struct {
    set s;
    key k;
    packed_set p;
} key_set;

// given a key array and a set, check if the set is valid according to the key array
bool set_valid(key k, set s);

// builds the next set after a given set
// (currently k is not used, and the resulting set may not be valid according to set_valid())
// returns the next set as a 25-bit (32-bit really) int (also stores in param n)
key_set next_set(key k, set c);

// converts a row of the grid to a set and retrieves the key for that row
key_set row_to_set(grid g, uint8_t row_index);

// converts a column of the grid to a set and retrieves the key for that column
key_set col_to_set(grid g, uint8_t col_index);

// converts a set to a given row in the grid
void set_to_row(grid * g, uint8_t row_index, set s);

// converts a set to a given col in the grid
void set_to_col(grid * g, uint8_t col_index, set s);

// finds all the valid combinations for a given key and stores these and their
// count in a set_combos struct (reallocates the struct as needed)
// PLEASE REMEMBER TO free() MEMORY ALLOCATED BY THIS FUNCTION!
set_combos find_valid_sets(key k);

// finds all the valid combinations for all the rows and columns in a given grid
grid_combos find_valid_combos(grid g);

// frees dynamically allocated memory contained within the rows and cols of a given grid_combos struct
void free_grid_combos(grid_combos g);

// returns a square_pairs struct storing pointers to all possible pairs of valid sets
// for each square in the grid - takes a grid_combos struct as sole argument
square_pairs find_square_combos(grid_combos g);

// frees dynamically allocated memory contained within the pointer arrays of a
// square_pairs struct
void free_square_pairs(square_pairs s);
