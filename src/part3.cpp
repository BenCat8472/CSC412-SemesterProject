#include "part3.h"


bool factoring_menu() {
    string s;
    int option;

    fputs("Select the factoring method:\n"
          "0) Fermats\n1) Pollard Rho\n2) Pollard p - 1\n3) Shanks\n> ", stdout);
    cin >> option;

    if ( option < 0 || option > 3 ) {
        return false;
    }

    fputs("Give the number to factor (in base 10): ", stdout);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, s);
    BigInt n = conv<BigInt>(s.c_str());

    BigInt f = factor(n, (FactoringMethod)option);
    if ( 1 < f && f < n ) {
        cout << n << " can be factored as " << f << " * " << n / f << std::endl;
    } else {
        puts("No non-trivial factors were found.");
    }

    return true;
}


bool generate_prime_menu() {
    long b;

    puts("This generates a prime in range [2^b - 1, 2^(b+1) - 1]");
    fputs("Give b (in base 10): ", stdout);
    cin >> b;

    BigInt p = random_prime(b);

    cout << "p = " << p << std::endl;

    return true;
}


bool RSA_menu() {
    char option;
    fputs("Generate keys? (y/n): ", stdout);
    cin >> option;

    if ( option == 'y' ) {
        BigInt n, e, d;
        RSA_key_gen(n, e, d);
        cout << "\tn = " << n << std::endl;
        cout << "\te = " << e << std::endl;
        cout << "\td = " << d << '\n' << std::endl;
    } else {
        string s;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        fputs("Give the modulo, n (in base 10): ", stdout);
        getline(cin, s);
        BigInt n = conv<BigInt>(s.c_str());
        fputs("Give the text, m/c (in base 10): ", stdout);
        getline(cin, s);
        BigInt t = conv<BigInt>(s.c_str());
        fputs("Give the key, e/d (in base 10): ", stdout);
        getline(cin, s);
        BigInt k = conv<BigInt>(s.c_str());

        BigInt r = RSA(t, k, n);

        cout << "The result is:\n\t" << r << std::endl;
    }

    return true;
}


bool test_prime_menu() {
    string s;

    fputs("Give the number to test (in base 10): ", stdout);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, s);
    BigInt n = conv<BigInt>(s.c_str());

    cout << n << (is_prime(n) ? " is prime." : " is not prime.") << std::endl;

    return true;
}
