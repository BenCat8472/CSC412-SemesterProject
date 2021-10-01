#include "utility.h"


char chr(int i) {
    return i + 'A';
}


int ord(char c) {
    return c - 'A';
}


Frequencies frequency(string text) {
    Frequencies freq;

    sort(text.begin(), text.end());

    unsigned i = 0;
    while ( i < text.size() ) {
        char c = text[i];
        int count = 1;
        while ( (++i < text.size()) && (text[i] == c) )
            ++count;
        freq.push_back({c, float(count) / text.size()});
    }

    sort(
        freq.begin(), freq.end(),
        [](Frequency a, Frequency b) { return a.second > b.second; }
    );

    return freq;
}


string to_alphabet(const string& text, const string& alphabet) {
    string new_text {};
    new_text.reserve(text.size());

    for ( const char& c : text ) {
        if (find(alphabet.begin(), alphabet.end(), c) != alphabet.end())
            new_text += c;
    }

    return new_text;
}


string toupper(const string& s) {
    string new_text {};
    new_text.reserve(s.size());

    for ( const char& c : s )
        new_text += toupper(c);

    return new_text;
}
