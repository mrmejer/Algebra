#include "BarretReducer.h"

using namespace std;

const BigNum mod;
const BigNum inv;
const unsigned len = 0;

BarretReducer::BarretReducer(const BigNum &n) : mod(n), inv(n.inv((n.bits() + 1) << 1)), len((n.bits() + 1) << 1)  {}

/**
 * reduces x modulo n
 * - x < n^2
 * @param x the number being reduced
 */
void BarretReducer::reduce(BigNum& x)
{
    BigNum q = (x * inv) >> len;
    x -= q * mod;
    if(x >= mod) x -= mod;
}

/**
 * calculates a * b (mod n)
 * @param a first factor
 * @param b second factor
 * @return the product
 */
BigNum BarretReducer::mul(const BigNum& a, const BigNum& b) {
    BigNum res = a * b;
    reduce(res);
    return res;
}

BigNum BarretReducer::getModulo() { return mod; }