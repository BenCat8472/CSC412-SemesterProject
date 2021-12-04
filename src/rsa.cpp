#include "rsa.h"


ZZ RSA(ZZ m, ZZ e, ZZ n) {
    return PowerMod(m, e, n);
}


void gen_pq(ZZ& p, ZZ& q) {

}
