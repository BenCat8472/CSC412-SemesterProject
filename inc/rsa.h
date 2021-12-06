#pragma once
#include <stdlib.h>
#include "cryptomath.h"

constexpr int N_DIGITS = 300;


BigInt RSA(BigInt text, BigInt exponent, BigInt modulo);
void RSA_key_gen(BigInt& n, BigInt& e, BigInt& d);
