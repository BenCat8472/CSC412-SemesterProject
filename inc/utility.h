#pragma once
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using std::find;
using std::string;
using std::toupper;

typedef std::pair<char, float> Frequency;
typedef std::vector<Frequency> Frequencies;

constexpr const char * const ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr float STANDARD_FREQUENCIES[] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};


char chr(int i);
int ord(char c);
Frequencies frequency(string text);
string to_alphabet(const string& text, const string& alphabet);
string toupper(const string& s);
