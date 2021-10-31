#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"


/******************************************************************************/
/*                             Part I Test Cases                              */
/******************************************************************************/
#include "cryptomath.h"
#include "affinecipher.h"
#include "vigenerecipher.h"


TEST_CASE("cryptomath.h") {
    char gcdfmt[] = "gcd(%d, %d) = %d\n";

    SECTION("gcd") {
        Int a = 21, b = 14;

        CHECK(gcd(a, b) == 7);
        CHECK(gcd(a, b) == gcd(b, a));
    }

    SECTION("extendedgcd") {
        printf("\nextendedgcd tests:-\n");
        Int a = 12345, b = 11111;
        Int x = a, y = b;
        Int d = extendedgcd(x, y);

        CHECK(d == 1);
        CHECK(x == -2224);
        CHECK(y == 2471);
        CHECK(x * a + y * b == d);
    }

    SECTION("findModInverse") {
        Int a = 3, n = 7;
        Int ai = findModInverse(a, n);

        CHECK(ai * a % n == 1);
    }

    SECTION("is_prim_root") {
        CHECK( is_prim_root(3, 7));
        CHECK(!is_prim_root(3, 9));
    }

    SECTION("mod") {
        Int a = -5, n = 7;
        CHECK(mod(a, n) == a + n);
        a = 5;
        CHECK(mod(a, n) == a % n);
    }
}


TEST_CASE("Affine cipher") {
    Int a = 7, b = 2;
    string s = "THEQUICKBROWNFOXJUMPEDOVERTHELAZYDOG";

    SECTION("Section one") {
        CHECK(affine_E(1, 0, s) == s);
        CHECK(affine_D(a, b, affine_E(a, b, s)) == s);
    }

    SECTION("Section two") {
        CHECK(affine_E(a, b, s) == "FZEKMGQUJRWAPLWHNMIDEXWTERFZEBCVOXWS");
    }
}


TEST_CASE("Vigenère Cipher") {
    SECTION("Section one") {
        string key = "LEMON";
        string text = "ATTACKATDAWN";
        CHECK(vigenere_D(key, vigenere_E(key, text)) == text);
    }

    SECTION("Section two") {
        CHECK(vigenere_E("LEMON", "ATTACKATDAWN") == "LXFOPVEFRNHR");
    }
}



/******************************************************************************/
/*                            Part II Test Cases                              */
/******************************************************************************/
#include "simpleDES.h"
#include "DES.h"


TEST_CASE("Simplified DES-type Algorithm") {
    SECTION("Section one") {
        std::vector<std::pair<const byte, const byte>> vals = {
            {0, 0},
            {0xff, 0xff},
            {0b011001, 0b01010101},
            {0b100110, 0b10101010}
        };
        for ( unsigned i = 0; i < vals.size(); ++i ) {
            byte x = vals[i].first, y = vals[i].second;
            CHECK(simple_expand(x) == y);
        }

        CHECK(simple_f(0b100110, 0b01100101) == 0b000100);
    }

    SECTION("Section two") {
        uint16_t x   = 0b011100100110;
        uint16_t key = 0b01100101;
        CHECK(simpleDES(x, key, 1) == 0b100110011000);
    }
}


TEST_CASE("Full 64-bit DES") {
    const unsigned LOOPS = 100;
    srand(time(NULL));

    SECTION("32-bit permute") {
        uint8_t table1[32] = {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        };
        CHECK(permute(0b10000000000000000000000000000000, table1) == 0xffffffff);
        CHECK(permute(0b01111111111111111111111111111111, table1) == 0x00000000);

        uint8_t table2[32] = {
             1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
        };
        bool failed = false;
        for ( unsigned i = 0; i < LOOPS; ++i ) {
            uint32_t x = static_cast<uint32_t>(rand());
            if ( permute(x, table2) != x )
                failed = true;
        }
        CHECK(failed == false);
    }

    SECTION("64-bit permute") {
        uint8_t table_to_1[64];
        for ( unsigned i = 0; i < 64; ++i) table_to_1[i] = 1;

        CHECK(
            permute(((uint64_t)0b1 << 63) | 0x0, table_to_1)
                ==
            0xffffffffffffffff
        );
        CHECK(
            permute(((uint64_t)0b1 << 63) ^ (uint64_t)(-1), table_to_1)
                ==
            0x0000000000000000
        );

        uint8_t table_identity[64];
        for ( unsigned i = 0; i < 64; ++i ) table_identity[i] = i + 1;

        {
            bool failed = false;
            for ( unsigned i = 0; i < LOOPS; ++i ) {
                uint64_t x = (static_cast<uint64_t>(rand()) << 32) | static_cast<uint64_t>(rand());
                if ( permute(x, table_identity) != x )
                    failed = true;
            }
            CHECK(failed == false);
        }

        uint64_t msg = 0x0002000000000001;
        uint64_t res = 0x0000008000000002;
        CHECK(permute(msg,  IP_TABLE) == res);
        CHECK(permute(res, IPI_TABLE) == msg);
        CHECK(permute(permute(res, IP_TABLE), IPI_TABLE) == res);

        {
            bool failed = false;
            for ( unsigned i = 0; i < LOOPS; ++i ) {
                uint64_t x = (static_cast<uint64_t>(rand()) << 32) | static_cast<uint64_t>(rand());
                if ( permute(permute(x, IP_TABLE), IPI_TABLE) != x )
                    failed = true;
            }
            CHECK(failed == false);
        }
    }

    SECTION("expand") {
        std::vector<std::pair<const uint32_t, const uint64_t>> vals = {
            {0x00000000, 0x0000000000000000},
            {0xffffffff, 0x0000ffffffffffff},
            {0b00000000000000001111111111111111, 0b100000000000000000000001011111111111111111111110}
        };
        for ( unsigned i = 0; i < vals.size(); ++i ) {
            uint32_t x = vals[i].first;
            uint64_t y = vals[i].second;
            CHECK(expand(x) == y);
        }
    }

    SECTION("Key generation") {
        const uint64_t key = 0xaabb09182736ccdd;
        const uint64_t ans[16] = {
            0x194cd072de8c, 0x4568581abcce, 0x06eda4acf5b5, 0xda2d032b6ee3,
            0x69a629fec913, 0xc1948e87475e, 0x708ad2ddb3c0, 0x34f822f0c66d,
            0x84bb4473dccc, 0x02765708b5bf, 0x6d5560af7ca5, 0xc2c1e96a4bf3,
            0x99c31397c91f, 0x251b8bc717d0, 0x3330c5d9a36d, 0x181c5d75c66d
        };

        vector<uint64_t> keys = gen_keys(key);

        for ( unsigned i = 0; i < 16; ++i ) {
            CHECK(keys[i] == ans[i]);
        }
    }

    SECTION("S-boxes") {
        CHECK(SBOX1[0b00][0b0000] == 14);
        CHECK(SBOX1[0b11][0b1111] == 13);

        CHECK(index_s_box(Sbox::Sbox1, 0b000000) == 14);
        CHECK(index_s_box(Sbox::Sbox1, 0b111111) == 13);

        bool success = true;
        for ( unsigned i = 0; i < 4; ++i ) {
            for ( unsigned j = 0; j < 16; ++j ) {
                uint8_t byte = ((i & 0b10) << 4) | (j << 1) | (i & 0b1);
                if ( index_s_box(Sbox::Sbox6, byte) != SBOX6[i][j] )
                    success = false;
            }
        }
        CHECK(success);
    }

    SECTION("f function") {
        CHECK(f(0x0, 0x0) == f(0xffffffff, 0xffffffffffff));
        CHECK(f(0x0, 0x0) == permute(0b11101111101001110010110001001101, C_TABLE));
        CHECK(f(0xffffffff, 0x0) == permute(0b11011001110011100011110111001011, C_TABLE));

        uint64_t k  = 0x194cd072de8c;
        uint32_t l0 = 0x14a7d678;
        uint32_t r0 = 0x18ca18ad;
        uint32_t r1 = 0x5A78E394;
        CHECK((l0 ^ f(r0, k)) == r1);
    }

    SECTION("Full DES") {
        {
            uint64_t msg = 0x123456abcd132536;
            uint64_t key = 0xaabb09182736ccdd;
            uint64_t res = 0xc0b7a8d05f3a829c;

            CHECK(DES(msg, key) == res);
        }

        {
            uint64_t msg = 0x0123456789abcdef;
            uint64_t key = 0x133457799bbcdff1;
            uint64_t res = 0x85e813540f0ab405;

            CHECK(DES(msg, key) == res);
        }
    }
}
