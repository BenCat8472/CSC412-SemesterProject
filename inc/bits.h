#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;


struct Bits {
    uint64_t val;
    int num_bits;

    Bits(uint64_t x, int n) : val(x), num_bits(n) {}
};


ostream& operator<<(ostream& o, Bits bits);
