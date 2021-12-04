#include "cryptomath.h"


bool is_prime(BigInt n) {
    BigInt r(0);
    BigInt d(n - 1);
    while ( d % 2 == 0 ) {
        d /= 2;
        ++r;
    }
    return miller_rabin(n, r, d);
}


bool miller_rabin(const BigInt& n, const BigInt& r, const BigInt& d) {
    LOG("+miller_rabin(%ld, %ld, %ld)\n", NTL::conv<long>(n), NTL::conv<long>(r), NTL::conv<long>(d));
    // Miller-Rabin test
    if ( n < 1 ) {
        LOG("-miller_rabin\n");
        return false;
    }

    // calculate loop bounds
    BigInt bounds(floor(2 * pow(log(n), 2)));
    if ( bounds > n - 2 ) {
        bounds = n - 2;
    }

    LOG("Bounds: %ld\n", NTL::conv<long>(bounds));
    for ( BigInt a, i(1); (a = get_nth_prime(i)) < bounds; ++i ) {
        BigInt x = NTL::PowerMod(a, d, n);

        LOG("a = %ld, x = %ld\n", NTL::conv<long>(a), NTL::conv<long>(x));
        if ( (x == 1) || (x == -1) ) {
            continue;
        }
        for ( BigInt j(0); j < r - 1; ++j ) {
            x = NTL::SqrMod(x, n);
            if ( x == n - 1 ) {
                break;
            }
        }
        if ( x != n - 1 ) {
            LOG("-miller_rabin\n");
            return false;
        }
    }

    LOG("-miller_rabin\n");
    return true;
}
