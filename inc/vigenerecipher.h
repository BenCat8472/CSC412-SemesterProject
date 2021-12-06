#pragma once
#include "utility.h"


class VigenereSquare {
    char data[26][26];

public:
    VigenereSquare();
    const char * operator[](int index) const;
};

const VigenereSquare VIGENERE_SQUARE;


string vigenere_D(const string& key, const string& text);
string vigenere_E(const string& key, const string& text);
