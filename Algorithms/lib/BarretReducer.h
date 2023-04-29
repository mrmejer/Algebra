#ifndef PROJEKT_BARRET_REDUCER_H
#define PROJEKT_BARRET_REDUCER_H

#include <bits/stdc++.h>
#include "BigNum.h"

using namespace std;

class BarretReducer
{
private:
    const BigNum mod;
    const BigNum inv;
    const unsigned len;

public:

    BarretReducer(const BigNum &n);

    /**
     * reduces x modulo n
     * - x < n^2
     * @param x the number being reduced
     */
    void reduce(BigNum& x);

    /**
     * calculates a * b (mod n)
     * @param a first factor
     * @param b second factor
     * @return the product
     */
    BigNum mul(const BigNum& a, const BigNum& b);

    BigNum getModulo();
};

#endif