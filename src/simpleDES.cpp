#include "simpleDES.h"


uint16_t simpleDES(uint16_t msg, uint16_t key, unsigned rounds) {
    byte r = 0b111111 & msg;        // first six bits
    byte l = 0b111111 & (msg >> 6); // next six bits

    // rounds := the number of rounds for the Feistel system
    for ( unsigned i = 0; i < rounds; ++i ) {
        byte next = l ^ simple_f(r, key);
        l = r;
        r = next;
        key = (key << 1) | ((key & 0b100000000) >> 8);
    }

    return (l << 6) | r;
}


byte simple_expand(byte x) {
    byte y = 0;
    y |= x & 0b11;
    y |= (x & 0b110000) << 2;
    byte a = x & 0b1000;
    byte b = x & 0b0100;
    y |= (a >> 1) | (a << 1);
    y |= (b << 1) | (b << 3);
    return y;
}


byte simple_f(byte r, byte k) {
    byte x = simple_expand(r) ^ k;
    byte lh = S1[(x & 0b10000000) >> (8 - 1)][(x & 0b01110000) >> 4];
    byte rh = S2[(x & 0b00001000) >> (4 - 1)][(x & 0b00000111) >> 0];
    return (lh << 3) | rh;
}
