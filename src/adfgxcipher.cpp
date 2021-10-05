#include "adfgxcipher.h"


string adfgx_D(const string& key, const string& ctext) {
    string text {};
    text.reserve(ctext.size() / 2);

    vector<pair<char, string>> columns;
    for ( unsigned c = 0; c < key.size(); ++c )
        columns.emplace_back(chr(c), string(1, key[c]));

    sort(columns.begin(), columns.end(),
        [](pair<char, string> a, pair<char, string> b) {
            return a.second[0] < b.second[0];
        }
    );

    {
        int c = 0;
        long unsigned start = 0, end = -1;
        do {
            start = end + 1;
            end = ctext.find(' ', start);
            columns[c++].second = ctext.substr(start, end - start);
        } while ( end != string::npos );
    }

    sort(columns.begin(), columns.end());

    string intermediate {};
    for ( unsigned i = 0; i < ctext.size(); ++i )
        intermediate += columns[i % key.size()].second[i / key.size()];
    for ( unsigned i = 0; i + 1 < ctext.size() - (key.size() - 1); i += 2 )
        text += ADFGX_D_MAPPING.at(intermediate.substr(i, 2));

    return text;
}


string adfgx_E(const string& key, const string& text) {
    string cipher_text {};
    cipher_text.reserve(2 * text.size());

    for ( char c : text ) {
        if ( c == 'I' )
            c = 'J';
        cipher_text += ADFGX_E_MAPPING.at(c);
    }

    vector<pair<char, string>> columns;
    for ( unsigned i = 0; i < key.size(); ++i )
        columns.emplace_back(key[i], "");

    for ( unsigned i = 0; i < cipher_text.size(); ++i )
        columns[i % key.size()].second += cipher_text[i];

    sort(columns.begin(), columns.end());

    cipher_text = "";
    for ( unsigned i = 0; i < key.size() - 1; ++i )
        cipher_text += columns[i].second + ' ';
    cipher_text += columns[columns.size() - 1].second;

    return cipher_text;
}
