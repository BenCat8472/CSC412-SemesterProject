#pragma once
#include "cryptomath.h"


enum class FactoringMethod {
    Fermats, Pollard_Rho, Pollard_p_minus_one, Shanks
};


BigInt factor(const BigInt& n, FactoringMethod m);
BigInt factor_Fermats_method(const BigInt&);
BigInt factor_Pollard_rho(const BigInt&);
BigInt factor_Pollard_p_minus_one(const BigInt&);
BigInt factor_Shanks(const BigInt&);
