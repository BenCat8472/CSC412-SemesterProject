#ifndef __AFFINECIPHER__H__
#define __AFFINECIPHER__H__

#include "utility.h"
#include "cryptomath.h"

using std::string;


string affine_D(int a, int b, const string& text, int n=26);
string affine_E(int a, int b, const string& text, int n=26);


#endif//__AFFINECIPHER__H__
