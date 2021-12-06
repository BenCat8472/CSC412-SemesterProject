#pragma once
#include <algorithm>
#include <math.h>
#include <set>
#include <vector>
#include <NTL/ZZ.h>
#include "debug.h"

typedef NTL::ZZ BigInt;

using NTL::conv;


/******************************************************************************/
/*                       Template Function Declarations                       */
/******************************************************************************/
template<typename Int=int> Int extendedgcd(Int& a, Int& b);
template<typename Int=int> Int findModInverse(Int a, Int n);
template<typename Int=int> Int gcd(Int a, Int b);
template<typename Int=int> void gcd_shift(Int& curr, Int& next, Int quot);
template<typename Int=int> bool is_prim_root(Int a, Int n);
template<typename Int=int> Int mod(Int a, Int n);


/******************************************************************************/
/*                     Non-template Function Declarations                     */
/******************************************************************************/
unsigned long long get_nth_prime(unsigned long long n);
bool is_prime(const BigInt& n);
bool miller_rabin(const BigInt& n);
bool miller_rabin(const BigInt& n, const BigInt& r, const BigInt& d);
BigInt random_prime(long b);


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
