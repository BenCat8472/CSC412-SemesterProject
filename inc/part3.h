#pragma once
#include <iostream>
#include <limits>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include "cryptomath.h"
#include "factoring.h"
#include "rsa.h"

using std::cin;
using std::cout;
using std::string;


bool factoring_menu();
bool generate_prime_menu();
bool RSA_menu();
bool test_prime_menu();
