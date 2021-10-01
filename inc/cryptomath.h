#ifndef __CRYPTOMATH__H__
#define __CRYPTOMATH__H__

#include <algorithm>
#include "debug.h"

using std::swap;

typedef int Int; // in case Int needs to be changed to a larger datatype


Int extendedgcd(Int& a, Int& b);
Int findModInverse(Int a, Int n);
Int gcd(Int a, Int b);
bool is_prim_root(Int a, Int n);
Int mod(Int a, Int n);


#endif//__CRYPTOMATH__H__
