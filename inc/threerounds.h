#ifndef __THREE__ROUNDS__ATTAKC__H__
#define __THREE__ROUNDS__ATTAKC__H__

#include <set>
#include "simpleDES.h"
#include "bits.h"

using std::set;
using std::pair;


pair<set<byte>, set<byte>> three_rounds(uint16_t m1, uint16_t c1, uint16_t m2, uint16_t c2);


#endif//__THREE__ROUNDS__ATTAKC__H__
