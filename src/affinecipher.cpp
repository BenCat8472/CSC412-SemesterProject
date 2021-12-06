#include "affinecipher.h"


string affine_D(int a, int b, const string& text, int n) {
    int ai = findModInverse(a, n);
    string out {};

    for (const char& c : text)
        out += chr(mod(ai * (ord(c) - b), n));

    return out;
}


string affine_E(int a, int b, const string& text, int n) {
    string out {};

    for (const char& c : text)
        out += chr(mod(a * ord(c) + b, n));

    return out;
}
