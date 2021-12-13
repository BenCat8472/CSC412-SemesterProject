#include "rsa.h"


BigInt RSA(BigInt m, BigInt e, BigInt n) {
    return PowerMod(m, e, n);
}


void RSA_key_gen(BigInt& n, BigInt& e, BigInt& d) {
    // LOG("+RSA_key_gen(...)\n");
    // generate p and q
    int p_digits = (N_DIGITS / 4) + rand() % (N_DIGITS / 4);
    int q_digits = N_DIGITS - p_digits;
    BigInt p = random_prime(p_digits);
    BigInt q = random_prime(q_digits);

    // calculate n and phi(n)
    n = p * q;
    BigInt phi = (p - 1) * (q - 1);

    // generate e
    // e = (1 << (N_DIGITS / 4)) + 1;
    do {
        e = NTL::RandomBnd(phi) / 4;
    } while ( gcd(e, phi) != 1 );

    // generate d
    d = findModInverse(e, phi);

// #ifdef DEBUG
//     std::cerr << "p = " << p
//             << "\nq = " << q
//             << "\ne = " << e
//             << "\nd = " << d << std::endl;
// #endif//DEBUG
//     LOG("-RSA_key_gen\n");
}
