#include <stdbool.h>

#include "crack.h"


int main(int argc, char const *argv[])
{
    grid g = {};
    if(check_grid(g)) {
        return 0; 
    } else {
        return 1;
    }
}
