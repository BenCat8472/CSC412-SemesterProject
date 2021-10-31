#ifndef __PART__ONE__FUNCS__H__
#define __PART__ONE__FUNCS__H__

#include <stdio.h>
#include <iostream>
#include <limits>
#include <vector>
#include <deque>
#include "utility.h"
#include "adfgxcipher.h"
#include "affinecipher.h"
#include "vigenerecipher.h"

using std::cout;
using std::cin;
using std::deque;
using std::vector;


bool adfgx_menu();
bool affine_attack();
bool affine_menu();
bool frequency_menu();
bool vigenere_attack();
bool vigenere_menu();


#endif//__PART__ONE__FUNCS__H__
