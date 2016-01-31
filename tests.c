#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "crack.h"


bool test_set_valid() {
    key_set t = {
        .k = { 1, 7, 3, 1, 1, 2, 0, 0, 0 },
        .s = { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 },
    };
    bool should_be_true = set_valid(t);
    key_set f = {
        .k = { 1, 7, 3, 1, 1, 2, 0, 0, 0 },
        .s = { 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 },
    };
    bool should_be_false = set_valid(f);
    return (should_be_true && !should_be_false);
}

bool test_build_set() {
    key k[9] = { 2, 3, 5, 1, 3, 1, 0, 0, 0 };
    set s[25] = {};
    // the expected set
    set e[25] = { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 };
    // call build_set
    build_set(k, s);
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(s[i] != e[i]) {
            return false;
        }
    }
    return true;
}

bool test_build_set_is_valid() {
    // test that sets built with build_set() successfully validate as true by set_valid()
    key k[9] = { 1, 2, 1, 3, 5, 1, 2, 3, 0 };
    set s[25] = {};
    build_set(k, s);
    return set_valid(k, s);
}

bool test_next_set() {
    // test that next_set() can iterate a set
    key k[9] = {}; // dummy for now
    set c[25] = { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 };
    // expected result set
    set e[25] = { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 };
    set n[25] = {};
    // call next_set
    next_set(k, c, n);
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(n[i] != e[i]) {
            return false;
        }
    }
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
    key k[9] = {};
    set s[25] = {};
    // the expected key
    key ek[9] = { 1, 3, 2, 5, 4, 0, 0, 0, 0 };
    // the expected set
    set es[25] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 };
    // call row_to_set
    row_to_set(g, 7, s, k);
    // check if equal to expected key
    for(uint8_t i = 0; i < 9; i++) {
        if(k[i] != ek[i]) {
            return false;
        }
    }
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(s[i] != es[i]) {
            return false;
        }
    }
    return true;
}

bool test_set_to_row() {
    // test that set_to_row() converts a set to a row properly
    grid g = {};
    set s[25] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 };;
    // call set_to_row
    set_to_row(&g, 19, s);
    // check if equal to expected row
    for(uint8_t i = 0; i < 25; i++) {
        if(g.squares[19][i] != s[i]) {
            return false;
        }
    }
    return true;
}

bool test_col_to_set() {
    // test that col_to_set() converts a column to a set properly
    grid g = setup_grid_for_tests();
    key k[9] = {};
    set s[25] = {};
    // the expected key
    key ek[9] = { 5, 3, 2, 1, 3, 1, 2, 0, 0 };
    // the expected set
    set es[25] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1 };
    // call col_to_set
    col_to_set(g, 14, s, k);
    // check if equal to expected key
    for(uint8_t i = 0; i < 9; i++) {
        if(k[i] != ek[i]) {
            return false;
        }
    }
    // check if equal to expected set
    for(uint8_t i = 0; i < 25; i++) {
        if(s[i] != es[i]) {
            return false;
        }
    }
    return true;
}

bool test_set_to_col() {
    // test that set_to_col() converts a set to a column properly
    grid g = {};
    set s[25] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1 };;
    // call set_to_row
    set_to_col(&g, 3, s);
    // check if equal to expected row
    for(uint8_t i = 0; i < 25; i++) {
        if(g.squares[i][3] != s[i]) {
            return false;
        }
    }
    return true;
}

bool test_find_valid_sets() {
    // test that find_valid_sets() returns the correct number of valid sets for a given key
    key k[9] = { 7, 3, 1, 1, 7, 0, 0, 0, 0 };
    set s[25] = {};
    // expected patterns that will be found
    uint32_t expected[21] = {
        8345471,  16668543, 16684927, 16689023, 16690815, 16690942, 33314687,
        33331071, 33335167, 33336959, 33337086, 33363839, 33367935, 33369727,
        33369854, 33376127, 33377919, 33378046, 33381503, 33381630, 33381884,
    };
    // call find_valid_sets and store results in a set_combos struct
    set_combos results = find_valid_sets(k, s);
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
    key k[9] = { 1, 1, 1, 2, 1, 1, 0, 0, 0 };
    set s[25] = {};
    // call find_valid_sets and store results in a set_combos struct
    set_combos results = find_valid_sets(k, s);
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

int main(int argc, char const *argv[]) {
    int result = 0;
    printf("test_set_valid:\n");
    if(!test_set_valid()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_build_set:\n");
    if(!test_build_set()) {
        printf("FAIL\n");
        result = 1;
    } else {
        printf("PASS\n");
    }
    printf("test_build_set_is_valid:\n");
    if(!test_build_set_is_valid()) {
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
    return result;
}
