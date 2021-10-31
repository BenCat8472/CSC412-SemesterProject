#include "DES.h"


uint64_t DES(uint64_t msg, uint64_t key) {
    LOG("+DES(0x%016lx, 0x%016lx)\n", msg, key);
    msg = permute(msg, IP_TABLE);

    // L.R = msg
    uint32_t r = msg;
    uint32_t l = msg >> 32;

    vector<uint64_t> keys = gen_keys(key);

    LOG("L0  := 0x%08x; R0  := 0x%08x\n", l, r);

    for ( unsigned i = 0; i < 16; ++i ) {
        uint32_t ln = r;
        r = l ^ f(r, keys[i]);
        l = ln;

        LOG("L%02d := 0x%08x; R%02d := 0x%08x; key%02d := 0x%012lx\n",
            i + 1, l, i + 1, r, i + 1, keys[i]);
    }

    // msg = R.L
    msg = static_cast<uint64_t>(r) << 32 | static_cast<uint64_t>(l);

    // final permutation
    msg = permute(msg, IPI_TABLE);

    LOG("-DES()\n");
    return msg;
}


uint64_t expand(uint32_t r) {
    return permute<uint64_t>(r, EXPAND_TABLE, 32, 48);
}


uint32_t f(uint32_t r, uint64_t key) {
    uint64_t bs = expand(r) ^ key;   // 48 bits := B1B2...B8, where Bj has six bits
    uint32_t c = 0;

    for ( unsigned i = 0; i < 8; ++i ) {
        // extract leading 6-bits, next 6-bits, etc.
        byte x = (bs >> (6 * (7 - i))) & (uint64_t)0b111111;
        c |= static_cast<uint32_t>(index_s_box((Sbox)i, x)) << (4 * (7 - i));
    }

    return permute(c, C_TABLE);
}


vector<uint64_t> gen_keys(uint64_t key) {
    // permute and remove parity bits
    uint64_t key56 = permute<uint64_t>(key, KEY_PARITY_TABLE, 64, 56);

    // split key into two 28-bit sections
    uint64_t d = 0xfffffff & key56;
    uint64_t c = 0xfffffff & key56 >> 28;

    vector<uint64_t> keys;
    keys.reserve(16);
    static const unsigned shifts[] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
    };
    for ( unsigned i = 0; i < 16; ++i ) {
        // do a 28-bit left rotation of shift amount on each half
        unsigned shift = shifts[i];
        uint64_t mask = shift == 1 ? 0b1 : 0b11;
        c = ((c << shift) & 0xfffffff) | ((c >> (28 - shift)) & mask);
        d = ((d << shift) & 0xfffffff) | ((d >> (28 - shift)) & mask);
        // recombine and permute for next key
        keys.push_back(permute(c << 28 | d, KEY_TABLE, 56, 48));
    }

    return keys;
}


uint8_t index_s_box(Sbox sbox, byte b) {
    unsigned i = ((b & 0b100000) >> 4) | (b & 0b1);
    unsigned j =  (b & 0b011110) >> 1;
    switch( sbox ) {
        case Sbox::Sbox1: return SBOX1[i][j];
        case Sbox::Sbox2: return SBOX2[i][j];
        case Sbox::Sbox3: return SBOX3[i][j];
        case Sbox::Sbox4: return SBOX4[i][j];
        case Sbox::Sbox5: return SBOX5[i][j];
        case Sbox::Sbox6: return SBOX6[i][j];
        case Sbox::Sbox7: return SBOX7[i][j];
        case Sbox::Sbox8: return SBOX8[i][j];
        default:
            LOG("Error: sbox value is out of range! (incorrect cast?)\n");
            return 0; // keeps the compiler quiet
    }
}
