#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "crack.h"


bool test_set_valid() {
    key tk = { { 1, 7, 3, 1, 1, 2, 0, 0, 0 } };
    set ts = { { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 } };
    bool should_be_true = set_valid(tk, ts);
    key fk = { { 1, 7, 3, 1, 1, 2, 0, 0, 0 } };
    set fs = { { 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 } };
    bool should_be_false = set_valid(fk, fs);
    return (should_be_true && !should_be_false);
}

bool test_next_set() {
    // test that next_set() can iterate a set
    key k = {}; // dummy for now
    set c = { { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 } };
    // expected result set
    set e = { { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 } };
    // call next_set
    key_set result = next_set(k, c);
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        // printf("%d %d\n", result.s.items[i], e.items[i]);
        if(result.s.items[i] != e.items[i]) {
            return false;
        }
    }
    // printf("\n");
    return true;
}

grid setup_grid_for_tests() {
    grid g = {
        .row_keys = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 3, 2, 5, 4, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        },
        .col_keys = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 5, 3, 2, 1, 3, 1, 2, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        },
        .squares = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        }
    };
    return g;
}

bool test_row_to_set() {
    // test that row_to_set() converts a row to a set properly
    grid g = setup_grid_for_tests();
    // the expected key
    key ek = { { 1, 3, 2, 5, 4, 0, 0, 0, 0 } };
    // the expected set
    set es = { { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 } };
    // call row_to_set
    key_set result = row_to_set(g, 7);
    // check if equal to expected key
    for(uint8_t i = 0; i < 9; i++) {
        if(result.k.items[i] != ek.items[i]) {
            return false;
        }
    }
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(result.s.items[i] != es.items[i]) {
            return false;
        }
    }
    return true;
}

bool test_col_to_set() {
    // test that col_to_set() converts a column to a set properly
    grid g = setup_grid_for_tests();
    // the expected key
    key ek = { { 5, 3, 2, 1, 3, 1, 2, 0, 0 } };
    // the expected set
    set es = { { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1 } };
    // call col_to_set
    key_set result = col_to_set(g, 14);
    // check if equal to expected key
    for(uint8_t i = 0; i < 9; i++) {
        if(result.k.items[i] != ek.items[i]) {
            return false;
        }
    }
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(result.s.items[i] != es.items[i]) {
            return false;
        }
    }
    return true;
}

bool test_set_to_row() {
    // test that set_to_row() converts a set to a row properly
    grid g = {};
    set s = { { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 } };
    // call set_to_row
    set_to_row(&g, 19, s);
    // check if equal to expected row
    for(uint8_t i = 0; i < 25; i++) {
        if(g.squares[19][i] != s.items[i]) {
            return false;
        }
    }
    return true;
}

bool test_set_to_col() {
    // test that set_to_col() converts a set to a column properly
    grid g = {};
    set s = { { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 } };
    // call set_to_row
    set_to_col(&g, 3, s);
    // check if equal to expected row
    for(uint8_t i = 0; i < 25; i++) {
        if(g.squares[i][3] != s.items[i]) {
            return false;
        }
    }
    return true;
}

bool test_find_valid_sets() {
    // test that find_valid_sets() returns the correct number of valid sets for a given key
    key k = { { 7, 3, 1, 1, 7, 0, 0, 0, 0 } };
    // expected patterns that will be found
    uint32_t expected[21] = {
        8345471,  16668543, 16684927, 16689023, 16690815, 16690942, 33314687,
        33331071, 33335167, 33336959, 33337086, 33363839, 33367935, 33369727,
        33369854, 33376127, 33377919, 33378046, 33381503, 33381630, 33381884,
    };
    // call find_valid_sets and store results in a set_combos struct
    set_combos results = find_valid_sets(k);
    // check the expected number of valid patterns were found
    if(results.count != 21) {
        return false;
    }
    // check the patterns found were expected
    for(uint8_t i = 0; i < 21; i++) {
        if((uint32_t)results.sets[i] != expected[i]) {
            return false;
        }
    }
    // DONT FORGET TO FREE DYNAMIC MEMORY!
    free(results.sets);
    return true;
}

bool test_find_valid_sets_realloc() {
    // test that find_valid_sets() returns the correct number of valid sets for a given key,
    // and that it reallocates plenty memory (this known set generates in excess of 20k results)
    key k = { { 1, 1, 1, 2, 1, 1, 0, 0, 0 } };
    // call find_valid_sets and store results in a set_combos struct
    set_combos results = find_valid_sets(k);
    // check the expected number of valid patterns were found
    if(results.count != 27132) {
        return false;
    }
    // DONT FORGET TO FREE DYNAMIC MEMORY!
    free(results.sets);
    return true;
}

bool test_free_grid_combos() {
    grid_combos g = {};
    free_grid_combos(g);
    return true;
}

bool test_free_square_pairs() {
    square_pairs sq = {};
    free_square_pairs(sq);
    return true;
}

int main(int argc, char const *argv[]) {
    int result = 0;
    printf("test_set_valid:\n");
    if(!test_set_valid()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_next_set:\n");
    if(!test_next_set()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_row_to_set:\n");
    if(!test_row_to_set()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_set_to_row:\n");
    if(!test_set_to_row()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_col_to_set:\n");
    if(!test_col_to_set()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_set_to_col:\n");
    if(!test_set_to_col()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_find_valid_sets:\n");
    if(!test_find_valid_sets()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_find_valid_sets_realloc:\n");
    if(!test_find_valid_sets_realloc()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_free_grid_combos:\n");
    if(!test_free_grid_combos()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_free_square_pairs:\n");
    if(!test_free_square_pairs()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    return result;
}
