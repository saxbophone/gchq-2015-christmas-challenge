#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "crack.h"


bool test_set_valid() {
    key tk[9] = { 1, 7, 3, 1, 1, 2, 0, 0, 0 };
    set ts[25] = { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 };
    bool should_be_true = set_valid(tk, ts);
    key fk[9] = { 1, 7, 3, 1, 1, 2, 0, 0, 0 };
    set fs[25] = { 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 };
    bool should_be_false = set_valid(fk, fs);
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

int main(int argc, char const *argv[]) {
    int result = 0;
    if(!test_set_valid()) {
        printf("FAIL: test_set_valid\n");
        result = 1;
    }
    if(!test_build_set()) {
        printf("FAIL: test_build_set\n");
        result = 1;
    }
    if(!test_build_set_is_valid()) {
        printf("FAIL: test_build_set_is_valid\n");
        result = 1;
    }
    return result;
}
