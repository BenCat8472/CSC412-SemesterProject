#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "cryptomath.h"
#include "affinecipher.h"
#include "vigenerecipher.h"


TEST_CASE("cryptomath.h") {
    char gcdfmt[] = "gcd(%d, %d) = %d\n";

    SECTION("gcd") {
        Int a = 21, b = 14;
        // printf(gcdfmt, a, b, gcd(a, b));
        // swap(a, b);
        // printf(gcdfmt, a, b, gcd(a, b));

        CHECK(gcd(a, b) == 7);
        CHECK(gcd(a, b) == gcd(b, a));
    }

    SECTION("extendedgcd") {
        printf("\nextendedgcd tests:-\n");
        Int a = 12345, b = 11111;
        Int x = a, y = b;
        Int d = extendedgcd(x, y);
        // printf(gcdfmt, a, b, d);
        // printf("%d*%d + %d*%d = %d\n", x, a, y, b, d);
        // printf("%d = %d\n", x*a + y*b, d);

        CHECK(d == 1);
        CHECK(x == -2224);
        CHECK(y == 2471);
        CHECK(x * a + y * b == d);
    }

    SECTION("findModInverse") {
        Int a = 3, n = 7;
        Int ai = findModInverse(a, n);
        // printf("%d = %d^-1 mod %d\n", ai, a, n);
        // printf("%d = 1\n", ai * a % n);

        CHECK(ai * a % n == 1);
    }

    SECTION("is_prim_root") {
        // Int g = 3, n = 7;
        // printf("%d %s a primitive root of Z_%d\n",
        //     g, (is_prim_root(g, n) ? "is" : "is not"), n);
        // g = 3, n = 9;
        // printf("%d %s a primitive root of Z_%d\n",
        //     g, (is_prim_root(g, n) ? "is" : "is not"), n);

        CHECK(is_prim_root(3, 7));
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
