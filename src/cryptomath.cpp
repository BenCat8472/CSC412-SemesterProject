#include "cryptomath.h"


void gcd_shift(Int& a, Int& b, Int q);  // helper func for extendedgcd


// returns gcd(a, b) and modifies a and b to be x and y s.t. x*a + y*b = 1
Int extendedgcd(Int& a, Int& b) {
    Int x = 1, y = 0;
    Int next_x = 0, next_y = 1;

    while ( b != 0 ) {
        LOG("x=% d, y=% d\n", x, y);

        Int quotient = a / b;
        gcd_shift(x, next_x, quotient);
        gcd_shift(y, next_y, quotient);

        a = a % b;
        swap(a, b);
    }
    LOG("x=% d, y=% d\n", x, y);

    Int gcd_ab = a;
    a = x;
    b = y;
    return gcd_ab;
}


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


Int gcd(Int a, Int b) {
    while ( b != 0 ) {
        a = a % b;
        swap(a, b);
    }
    return a;
}


void gcd_shift(Int& curr, Int& next, Int quot) {
    Int temp = next;
    next = curr - quot * next;
    curr = temp;
}


// assumes 0 <= a < n
bool is_prim_root(Int a, Int n) {
    Int* field = new Int[n];
    if ( field == nullptr )
        throw "Memory allocation failed.";

    for ( Int i = 0; i < n; i += 1 )
        field[i] = i;

    field[a] = 0;
    for ( Int x = a * a % n; (x != a) && (x != 0); x = (x * a) % n )
        field[x] = 0;

    bool primitive = true;
    for ( Int i = 0; i < n; i += 1 ) {
        if ( field[i] != 0 )
            primitive = false;
    }

    delete[] field;

    return primitive;
}


// positive modulo
Int mod(Int a, Int n) {
    return ((a % n) + n) % n;
}
