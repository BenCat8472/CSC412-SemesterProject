#include "vigenerecipher.h"


VigenereSquare::VigenereSquare() {
    for ( int i = 0; i < 26; ++i ) {
        int k = i;
        for ( int j = 0; j < 26; ++j )
            data[i][j] = ALPHABET[k++ % 26];
    }
}

const char * VigenereSquare::operator[](int index) const {
    return (const char *) data[index];
}


string vigenere_D(const string& key, const string& cipher_text) {
    string text;
    text.reserve(cipher_text.size());

    int i = 0, j;
    for ( const char& c : cipher_text ) {
        const char * ROW = VIGENERE_SQUARE[ord(key[i++ % key.size()])];
        for ( j = 0; (j < 26) && (ROW[j] != c); j++ );
        text += ALPHABET[j];
    }

    return text;
}


string vigenere_E(const string& key, const string& text) {
    string cipher_text;
    cipher_text.reserve(text.size());

    int i = 0;
    for ( const char& c : text )
        cipher_text += VIGENERE_SQUARE[ord(key[i++ % key.size()])][ord(c)];

    return cipher_text;
}
