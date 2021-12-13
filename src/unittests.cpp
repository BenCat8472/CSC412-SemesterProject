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
        {
            int a = 21, b = 14;

            CHECK(gcd(a, b) == 7);
            CHECK(gcd(a, b) == gcd(b, a));
        }
        {
            BigInt a(21), b(14);

            CHECK(gcd(a, b) == 7);
            CHECK(gcd(a, b) == gcd(b, a));
        }
    }

    SECTION("extendedgcd") {
        {
            int a = 12345, b = 11111;
            int x = a, y = b;
            int d = extendedgcd(x, y);

            CHECK(d == 1);
            CHECK(x == -2224);
            CHECK(y == 2471);
            CHECK(x * a + y * b == d);
        }
        {
            BigInt a(12345), b(11111);
            BigInt x = a, y = b;
            BigInt d = extendedgcd(x, y);

            CHECK(d == 1);
            CHECK(x == -2224);
            CHECK(y == 2471);
            CHECK(x * a + y * b == d);
        }
    }

    SECTION("findModInverse") {
        {
            int a = 3, n = 7;
            int ai = findModInverse(a, n);

            CHECK(ai * a % n == 1);
        }
        {
            BigInt a(3), n(7);
            BigInt ai = findModInverse(a, n);

            CHECK(ai * a % n == 1);
        }
    }

    SECTION("is_prim_root") {
        CHECK( is_prim_root(3, 7));
        CHECK(!is_prim_root(3, 9));
        CHECK( is_prim_root(27, 101));
        CHECK(!is_prim_root(13, 101));
        CHECK( is_prim_root(BigInt(27), BigInt(101)));
        CHECK(!is_prim_root(BigInt(13), BigInt(101)));
    }

    SECTION("mod") {
        int a = -5, n = 7;
        CHECK(mod(a, n) == a + n);
        a = 5;
        CHECK(mod(a, n) == a % n);
    }
}


TEST_CASE("Affine cipher") {
    int a = 7, b = 2;
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
#include "threerounds.h"


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


TEST_CASE("Three Rounds Attack") {
    SECTION("Example") {
        uint16_t key = 0b01001101; // 0b001001101;
        uint16_t m1 = 0b000111011011;
        uint16_t m2 = 0b101110011011;
        uint16_t c1 = 0b000011100101;
        uint16_t c2 = 0b100100011000;

        auto k4s = three_rounds(m1, c1, m2, c2);

        CHECK(k4s.first.find(0b1001) != k4s.first.end());
        CHECK(k4s.first.find(0b0011) != k4s.first.end());
        CHECK(k4s.second.find(0b1111) != k4s.second.end());
        CHECK(k4s.second.find(0b0100) != k4s.second.end());
    }
}


/******************************************************************************/
/*                            Part III Test Cases                             */
/******************************************************************************/
#include "factoring.h"
#include "rsa.h"


TEST_CASE("factoring") {
    const vector<BigInt> composites = {
        BigInt(2 * 3), BigInt(17 * 41), BigInt(709 * 719), BigInt(7333 * 7333),
        BigInt(2 * 7919), BigInt(2003 * 4001) * BigInt(6007 * 8009)
    };

    SECTION("Fermat's method") {
        std::cerr << "Fermat's method:" << std::endl;
        bool failed = false;
        for ( const BigInt& n : composites ) {
            BigInt p = factor_Fermats_method(n);
            BigInt q = n / p;
            std::cerr << n << " = " << p << " * " << q << std::endl;
            if ( p * q != n ) {
                failed = true;
            }
        }
        CHECK(!failed);
    }

    SECTION("Pollard's rho") {
        std::cerr << "Pollard's rho:" << std::endl;
        bool failed = false;
        for ( const BigInt& n : composites ) {
            BigInt p = factor_Pollard_rho(n);
            BigInt q = n / p;
            std::cerr << n << " = " << p << " * " << q << std::endl;
            if ( p * q != n ) {
                failed = true;
            }
        }
        CHECK(!failed);
    }

    SECTION("Pollard's p-1") {
        std::cerr << "Pollard's p-1:" << std::endl;
        bool failed = false;
        for ( const BigInt& n : composites ) {
            BigInt p = factor_Pollard_p_minus_one(n);
            BigInt q = n / p;
            std::cerr << n << " = " << p << " * " << q << std::endl;
            if ( p * q != n ) {
                failed = true;
            }
        }
        CHECK(!failed);
    }

    SECTION("Shank's Square Forms") {
        std::cerr << "Shank's Square Forms:" << std::endl;
        bool failed = false;
        for ( const BigInt& n : composites ) {
            BigInt p = factor_Shanks(n);
            BigInt q = n / p;
            std::cerr << n << " = " << p << " * " << q << std::endl;
            if ( p * q != n ) {
                failed = true;
            }
        }
        CHECK(!failed);
    }
}


TEST_CASE("prime generation") {
    SECTION("get_nth_prime") {
        CHECK(get_nth_prime(    1) ==      2);
        CHECK(get_nth_prime(   10) ==     29);
        CHECK(get_nth_prime(  100) ==    541);
        CHECK(get_nth_prime( 1000) ==   7919);
        CHECK(get_nth_prime(10000) == 104729);
    }

    SECTION("miller_rabin") {
        CHECK( miller_rabin(BigInt(2)));
        CHECK(!miller_rabin(BigInt(4)));
        CHECK( miller_rabin(BigInt(7477)));
        CHECK(!miller_rabin(BigInt(1025)));
        CHECK( miller_rabin(BigInt(472882049)));
        CHECK(!miller_rabin(BigInt(472882051)));
        CHECK( miller_rabin(BigInt(491495357)));
        CHECK(!miller_rabin(BigInt(491495413)));
        CHECK( miller_rabin(BigInt(961903451)));
        CHECK(!miller_rabin(BigInt(961903481)));
    }

    SECTION("random_prime") {
        NTL::SetSeed(BigInt(time(NULL)));
        bool passed = true;
        for ( int i = 0; i < 100; ++i ) {
            long b = 1 + rand() % 63;
            BigInt r = random_prime(b);

            if ( !(NTL::power(BigInt(2), b) - 1 <= r) ||
                 !(r <= NTL::power(BigInt(2), b + 1) - 1) ||
                 !is_prime(r) ) {
                passed = false;
            }
        }
        CHECK(passed);
    }
}


TEST_CASE("RSA") {
    SECTION("given") {
        BigInt n, e, d;
        RSA_key_gen(n, e, d);

        BigInt m(42);
        BigInt c = RSA(m, e, n);
        CHECK(RSA(c, d, n) == m);
    }

    SECTION("random") {
        srand(time(NULL));

        bool passed = true;
        for ( int i = 0; i < 16; ++i ) {
            BigInt n, e, d;
            RSA_key_gen(n, e, d);

            BigInt m = NTL::RandomBnd(n);
            BigInt c = RSA(m, e, n);
            passed &= (RSA(c, d, n) == m);
        }
        CHECK(passed);
    }
}
