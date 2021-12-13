#include "factoring.h"


static BigInt Pollard_g(const BigInt& x, const BigInt& n);


BigInt factor(const BigInt& n, FactoringMethod method) {
    switch(method) {
        case FactoringMethod::Fermats:
            return factor_Fermats_method(n);
        case FactoringMethod::Pollard_Rho:
            return factor_Pollard_rho(n);
        case FactoringMethod::Pollard_p_minus_one:
            return factor_Pollard_p_minus_one(n);
        case FactoringMethod::Shanks:
            return factor_Shanks(n);
        default:
            return BigInt(0);
    }
}


BigInt factor_Fermats_method(const BigInt& n) {
    if ( n % 2 == 0 ) { // Fermat's method should only be used on odd numbers
        return BigInt(2);
    }

    BigInt a, b, r;
    // a = floor(sqrt(n)) # (- 1, due to loop)
    a = NTL::SqrRoot(n);
    if ( NTL::sqr(a) == n ) {
        a -= 1;
    }

    do {
        a += 1;
        b = NTL::sqr(a) - n;
        r = NTL::SqrRoot(b);
    } while ( NTL::sqr(r) != b );

    return a - r;
}


static BigInt Pollard_g(const BigInt& x, const BigInt& n) {
    // we use g(x) = x^2 + 1 (mod n)
    return (NTL::SqrMod(x, n) + 1) % n;
}


BigInt factor_Pollard_rho(const BigInt& n) {
    BigInt x(2), y(2), d(1);

    while ( d == 1 ) {
        x = Pollard_g(x, n);
        y = Pollard_g(Pollard_g(y, n), n);
        d = gcd(abs(x - y), n);
    }

    return d;
}


BigInt factor_Pollard_p_minus_one(const BigInt& n) {
    BigInt a(2);
    BigInt d(1);

    for ( BigInt B(1); !(1 < d && d < n); ++B ) {
        BigInt b = a;
        for ( BigInt i(2); i <= B; ++i ) { // b = a^(B!) (mod n)
            b = NTL::PowerMod(b, i, n);
        }

        d = gcd(b - 1, n);
    }

    return d;
}


BigInt factor_Shanks(const BigInt& n) {
    // check if n is a perfect square
    BigInt r = NTL::SqrRoot(n);
    if ( r * r == n ) {
        return r;
    }

    // Xi is the ith X where l = i - 1 and n = i + 1
    // i.e., Ql is the last Q and Qn is the next Q (after Qi the current Q)
    BigInt P0, Pl, Pi;
    BigInt Q0, Q1, Ql, Qi, Qn;
    BigInt b0, bi;

    // loop until a suitable candidate is found
    BigInt candidate(1);
    for ( int k = 1; !(1 < candidate && candidate < n); ++k ) {
        const BigInt kn(k * n);

        P0 = NTL::SqrRoot(kn);
        Q0 = BigInt(1);
        Q1 = kn - NTL::sqr(P0);

        Pi = P0;
        Pl = P0;
        Ql = Q0;
        Qi = Q1;

        for ( int i = 2; ; ++i ) {
            bi = (P0 + Pl) / Qi;
            Pi = bi * Qi - Pl;
            Qn = Ql + bi * (Pl - Pi);

            r = NTL::SqrRoot(Qn);
            if ( (i % 2 == 0) && NTL::sqr(r) == Qn ) {
                break;
            }

            Ql = Qi;
            Qi = Qn;
            Pl = Pi;
        }

        b0 = (P0 - Pi) / r;
        P0 = b0 * r + Pi;
        Q0 = r;
        Q1 = (kn - NTL::sqr(P0)) / Q0;

        Pi = P0;
        Pl = P0;
        Ql = Q0;
        Qi = Q1;

        for (;;) {
            bi = (P0 + Pl) / Qi;
            Pi = bi * Qi - Pl;
            Qn = Ql + bi * (Pl - Pi);

            if ( abs(Pi) == abs(Pl) ) {
                break;
            }

            Ql = Qi;
            Qi = Qn;
            Pl = Pi;
        }

        candidate = gcd(Pi, n);
    }

    return candidate;
}
