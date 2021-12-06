#pragma once
#include <map>
#include "utility.h"

using std::vector;
using std::pair;

const std::map<const string, const char> ADFGX_D_MAPPING = {
    {"AA", 'X'}, {"AD", 'R'}, {"AF", 'G'}, {"AG", 'E'}, {"AX", 'P'},
    {"DA", 'S'}, {"DD", 'O'}, {"DF", 'F'}, {"DG", 'J'}, {"DX", 'L'},
    {"FA", 'B'}, {"FD", 'D'}, {"FF", 'H'}, {"FG", 'C'}, {"FX", 'Z'},
    {"GA", 'W'}, {"GD", 'A'}, {"GF", 'V'}, {"GG", 'U'}, {"GX", 'N'},
    {"XA", 'Y'}, {"XD", 'M'}, {"XF", 'K'}, {"XG", 'T'}, {"XX", 'Q'}
};

const std::map<const char, const string> ADFGX_E_MAPPING = {
    {'X', "AA"}, {'R', "AD"}, {'G', "AF"}, {'E', "AG"}, {'P', "AX"},
    {'S', "DA"}, {'O', "DD"}, {'F', "DF"}, {'J', "DG"}, {'L', "DX"},
    {'B', "FA"}, {'D', "FD"}, {'H', "FF"}, {'C', "FG"}, {'Z', "FX"},
    {'W', "GA"}, {'A', "GD"}, {'V', "GF"}, {'U', "GG"}, {'N', "GX"},
    {'Y', "XA"}, {'M', "XD"}, {'K', "XF"}, {'T', "XG"}, {'Q', "XX"}
};


string adfgx_D(const string& key, const string& text);
string adfgx_E(const string& key, const string& text);
