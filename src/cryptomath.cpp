#include "cryptomath.h"


unsigned long long get_nth_prime(unsigned long long n) {
    static std::vector<unsigned long long> primes {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67
    };

    while ( n >= primes.size() ) {
        for ( int x = primes.back() + 2; true; x += 2 ) {
            auto it = primes.begin();
            for (; it != primes.end() && (x % *it != 0); ++it );
            if ( it == primes.end() ) {
                primes.push_back(x);
                break;
            }
        }
    }

    return primes[n - 1];
}


bool is_prime(const BigInt& n) {
    return miller_rabin(n);
}


bool miller_rabin(const BigInt& n) {
    if ( (n <= 1) || ((n % 2 == 0) && (n != 2)) ) {
        return false;
    }

    BigInt r(0);
    BigInt d(n - 1);
    while ( d % 2 == 0 ) {
        d >>= 1;
        ++r;
    }

    return miller_rabin(n, r, d);
}


bool miller_rabin(const BigInt& n, const BigInt& r, const BigInt& d) {
    // LOG("+miller_rabin(%ld, %ld, %ld)\n", conv<long>(n), conv<long>(r), conv<long>(d));
    if ( (n <= 1) || ((n % 2 == 0) && (n != 2)) ) {
        // LOG("-miller_rabin -> false\n");
        return false;
    }

    // calculate loop bounds
    BigInt bounds(floor(2 * pow(log(n), 2)));
    if ( bounds > n - 2 ) {
        bounds = n - 2;
    }

    // LOG("Bounds: 2 <= a <= %ld, where a is prime.\n", conv<long>(bounds));
    BigInt a;
    for ( unsigned long long i = 1; (a = get_nth_prime(i)) <= bounds; ++i ) {
        BigInt x = NTL::PowerMod(a, d, n);

        if ( x != 1 ) {
            for ( int j = 0; (x != n - 1) && (j < r - 1); ++j ) {
                x = NTL::SqrMod(x, n);
            }

            if ( x != n - 1 ) {
                // LOG("Witness found: a = %ld\n", conv<long>(a));
                // LOG("-miller_rabin -> false\n");
                return false;
            }
        }
    }

    // LOG("-miller_rabin -> true\n");
    return true;
}


BigInt random_prime(long b) {   // generates a prime in range [2^b - 1, 2^(b+1) - 1]
    DTHROW_IF(b == 0, "b must be > 0!");
    BigInt b0 = NTL::power(BigInt(2), b);

    for (;;) {
        BigInt r = b0 + NTL::RandomBnd(b0) - 1;
        if ( miller_rabin(r) ) {
            return r;
        }
    }
}
