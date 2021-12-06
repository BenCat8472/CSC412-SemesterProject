#pragma once
#include <iostream>
#include <limits>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include "simpleDES.h"
#include "DES.h"
#include "threerounds.h"

using std::cin;
using std::hex;
using std::string;


bool full_DES_menu();
uint16_t get_binary();
bool simple_DES_menu();
bool three_rounds_menu();
