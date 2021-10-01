#include "adfgxcipher.h"


string adfgx_D(const string& key, const string& cipher_text) {
    string text {};
    text.reserve(cipher_text.size() / 2);

    for ( unsigned i = 0; i + 1 < cipher_text.size(); i += 2 ) {
        text += ADFGX_D_MAPPING.at(string() + cipher_text[i] + cipher_text[i + 1]);
    }

    return text;
}


string adfgx_E(const string& key, const string& text) {
    string cipher_text {};
    cipher_text.reserve(2 * text.size());

    for ( const char& c : text )
        cipher_text += ADFGX_E_MAPPING.at(c);

    vector<pair<char, string>> columns;
    for ( unsigned i = 0; i < key.size(); ++i )
        columns.emplace_back(key[i], "");
    for ( unsigned i = 0, j = 0; i < cipher_text.size(); ++i, ++j )
        columns[j % key.size()].second += cipher_text[i];

    sort(columns.begin(), columns.end());

    cipher_text = "";
    for ( unsigned i = 0; i < key.size(); ++i )
        cipher_text += columns[i].second;
    return cipher_text;
}
