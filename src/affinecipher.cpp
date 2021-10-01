#include "affinecipher.h"

char shift(int a, int b, char c, int m=26) {
    return (a * (toupper(c) - 'A') + c) % m + 'A';
}

string affine(int a, int b, string text) {
    string out = "";
    for (char c : text) {
        out += shift(a, b, c);
    }
    return out;
}
