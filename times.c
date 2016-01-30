#include <stdbool.h>
#include <stdint.h>

#include "crack.h"


int main(int argc, char const *argv[]) {
    // roughly time how long it takes to check if a set is valid and iterate, 2^25 times
    key k[9] = { 1, 7, 3, 1, 1, 2, 0, 0, 0 };
    set s[25] = { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0 };
    for(uint64_t i = 0; i < 33554432; i++) {
        set_valid(k, s);
        next_set(k, s, s);
    }
    return 0;
}
