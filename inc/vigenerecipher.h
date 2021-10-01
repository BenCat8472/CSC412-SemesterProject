#ifndef __VIGENERECIPHER__H__
#define __VIGENERECIPHER__H__

#include "utility.h"


// const char* const* const vigenere_square() {
//     static bool done = false;
//     static char VIGENERE_SQUARE[26][26];
//
//     if ( !done ) {
//         for ( int i = 0; i < 26; ++i ) {
//             int k = i;
//             for ( int j = 0; j < 26; ++j )
//                 VIGENERE_SQUARE[i][j] = LETTERS[k++ % 26];
//         }
//         done = true;
//     }
//
//     return VIGENERE_SQUARE;
// }


class VigenereSquare {
    char data[26][26];

public:
    VigenereSquare();
    const char * operator[](int index) const;
};

const VigenereSquare VIGENERE_SQUARE;


string vigenere_D(const string& key, const string& text);
string vigenere_E(const string& key, const string& text);


#endif//__VIGENERECIPHER__H__
