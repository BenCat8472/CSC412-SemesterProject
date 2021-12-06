#pragma once
#include <NTL/ZZ.h>

using namespace NTL;


ZZ RSA(ZZ text, ZZ exponent, ZZ modulo);
void gen_pq(ZZ& p, ZZ& q);
