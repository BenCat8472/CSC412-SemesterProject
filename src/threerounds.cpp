#include "threerounds.h"


// Let Li Ri be some plaintext, and L*i R*i is some alternate plaintext.
// Let L'i R'i = Li Ri XOR L*i R*i
// Then, R'4 XOR L'1 = f(L4, K4) XOR f(L*4, K4), where Ki is the ith key

pair<set<byte>, set<byte>> three_rounds(uint16_t m1, uint16_t c1, uint16_t m2, uint16_t c2) {
    set<byte> k4l;
    set<byte> k4r;

    uint16_t l1 = 0b111111 & m1 >> 6;
    uint16_t r1 = 0b111111 & m1;

    uint16_t l4 = 0b111111 & c1 >> 6;
    uint16_t r4 = 0b111111 & c1;

    uint16_t l1s = 0b111111 & m2 >> 6;
    uint16_t r1s = 0b111111 & m2;

    uint16_t l4s = 0b111111 & c2 >> 6;
    uint16_t r4s = 0b111111 & c2;

    uint16_t l1p = l1 ^ l1s;
    uint16_t r4p = r4 ^ r4s;

    if ( r1 != r1s ) {
        printf("Error: R1 and R*1 do not match!\n");
        return make_pair(k4l, k4r);
    }

    uint16_t input_xor = simple_expand(l4) ^ simple_expand(l4s);
    byte input_sbox1_xor = input_xor >> 4;
    byte input_sbox2_xor = input_xor & 0b1111;

    uint16_t output_xor = r4p ^ l1p;
    byte sbox1_out_xor = output_xor >> 3;
    byte sbox2_out_xor = output_xor & 0b111;

    byte l4el = simple_expand(l4) >> 4;
    byte l4er = simple_expand(l4) & 0b1111;
    byte l4sel = simple_expand(l4s) >> 4;
    byte l4ser = simple_expand(l4s) & 0b1111;

    for ( unsigned i = 0; i < 16; ++i ) {
        for ( unsigned j = 0; j < 16; ++j ) {
            if ( (i ^ j ^ input_sbox1_xor) == 0 ) {
                byte sbox1_o1 = S1[(i & 0b1000) >> 3][i & 0b0111];
                byte sbox1_o2 = S1[(j & 0b1000) >> 3][j & 0b0111];
                if ( (sbox1_o1 ^ sbox1_o2 ^ sbox1_out_xor) == 0 ) {
                    k4l.emplace(i ^ l4el);
                    k4l.emplace(j ^ l4sel);
                }
            }
            if ( (i ^ j ^ input_sbox2_xor) == 0 ) {
                byte sbox2_o1 = S2[(i & 0b1000) >> 3][i & 0b0111];
                byte sbox2_o2 = S2[(j & 0b1000) >> 3][j & 0b0111];
                if ( (sbox2_o1 ^ sbox2_o2 ^ sbox2_out_xor) == 0 ) {
                    k4r.emplace(i ^ l4er);
                    k4r.emplace(j ^ l4ser);
                }
            }
        }
    }

#ifdef DEBUG
    cout << "K4 left half possibilities:\n";
    for ( auto x : k4l ) {
        cout << Bits(x, 4) << ' ';
    }
    cout << "\nK4 right half possibilities:\n";
    for ( auto x : k4r ) {
        cout << Bits(x, 4) << ' ';
    }
    cout << '\n';
#endif//DEBUG

    return make_pair(k4l, k4r);
}
