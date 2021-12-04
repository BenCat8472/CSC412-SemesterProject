#pragma once
#include <algorithm>
#include <math.h>
#include <set>
#include <list>
#include <NTL/ZZ.h>
#include "debug.h"

typedef NTL::ZZ BigInt;


/******************************************************************************/
/*                       Template Function Declarations                       */
/******************************************************************************/
template<typename Int=int> Int extendedgcd(Int& a, Int& b);
template<typename Int=int> Int findModInverse(Int a, Int n);
template<typename Int=int> Int gcd(Int a, Int b);
template<typename Int=int> void gcd_shift(Int& curr, Int& next, Int quot);
template<typename Int=int> Int get_nth_prime(Int n);
template<typename Int=int> bool is_prim_root(Int a, Int n);
template<typename Int=int> Int mod(Int a, Int n);
template<typename Int=int> Int random_prime(Int b);


/******************************************************************************/
/*                     Non-template Function Declarations                     */
/******************************************************************************/
bool is_prime(BigInt n);
bool miller_rabin(const BigInt& n, const BigInt& r, const BigInt& d);


/******************************************************************************/
/*                       Template Function Definitions                        */
/******************************************************************************/
template<typename Int>
Int extendedgcd(Int& a, Int& b) { // returns gcd(a, b); sets a and b to be x and y s.t. x*a + y*b = 1
    Int x(1), y(0);
    Int next_x(0), next_y(1);

    while ( b != 0 ) {
        Int quotient = a / b;
        gcd_shift(x, next_x, quotient);
        gcd_shift(y, next_y, quotient);

        a = a % b;
        std::swap(a, b);
    }

    Int gcd_ab = a;
    a = x;
    b = y;
    return gcd_ab;
}


template<typename Int>
Int findModInverse(Int a, Int n) {
    Int x = a, y = n;
    #ifdef DEBUG
        Int d = extendedgcd(x, y);
        if ( d != 1 )
            throw "'a' and 'n' are not relatively prime so a^-1 DNE!";
    #else
        extendedgcd(x, y);
    #endif
    while ( x < 0 )
        x += n;
    return x;
}


template<typename Int>
Int gcd(Int a, Int b) {
    while ( b != 0 ) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}


template<typename Int>
void gcd_shift(Int& curr, Int& next, Int quot) { // helper func for extendedgcd
    Int temp = next;
    next = curr - quot * next;
    curr = temp;
}


template<typename Int>
Int get_nth_prime(Int n) {
    LOG("+get_nth_prime\n");
    static std::list<Int> primes { Int(2), Int(3), Int(5), Int(7), Int(11) };

    while ( n >= 1 + primes.size() ) {
        for ( Int x = primes.back() + 2; true; x += 2 ) {
            auto it = primes.begin();
            for (; it != primes.end() && (x % *it != 0); ++it );
            if ( it == primes.end() ) {
                primes.push_back(x);
                break;
            }
        }
    }

    auto it = primes.rbegin();
    for ( Int j(0); j < primes.size() - n; ++j, ++it );

    LOG("-get_nth_prime\n");
    return *it;
}


template<typename Int>
bool is_prim_root(Int a, Int n) {
    DTHROW_IF(n < a, "'a' must be less than 'n' to be a primitive root.");
    // construct field
    std::set<Int> field;
    for ( Int i(1); i < n; ++i ) {
        field.emplace(i);
    }

    // remove powers of 'a' until it loops or hits zero
    field.erase(a);
    for ( Int x = (a * a) % n; (x != a) && (x != 0); x = (x * a) % n ) {
        field.erase(x);
    }

    // return if all elements of the field were reached
    return field.empty();
}


template<typename Int>
Int mod(Int a, Int n) { // positive modulo
    return ((a % n) + n) % n;
}


template<typename Int>
Int random_prime(Int b) {   // generates a prime in range [2^b - 1, 2^(b+1) - 1]
    Int b0 = NTL::power(2, b    ) - 1;
    Int b1 = NTL::power(2, b + 1) - 1;

    for ( Int n = b0; n < b1; ++n ) {
        if ( PowerMod(2, n - 1, n) == 1 ) {

        }
    }
}
