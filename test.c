#include <stdbool.h>
#include <stdint.h>

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


int main(int argc, char const *argv[]) {
    int result = 0;
    if(!test_set_valid()) {
        result = 1; 
    }
    return result;
}
