#ifndef __UTILITY__H__
#define __UTILITY__H__

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


char chr(int i);
int ord(char c);
Frequencies frequency(string text);
string to_alphabet(const string& text, const string& alphabet);
string toupper(const string& s);



#endif//__UTILITY__H__
