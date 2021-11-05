#include "bits.h"


ostream& operator<<(ostream& o, Bits bits) {
    o << "0b";
    for ( int i = bits.num_bits - 1; i >= 0; --i ) {
        o << (bits.val & (0b1 << i) ? '1' : '0');
    }

    return o;
}
