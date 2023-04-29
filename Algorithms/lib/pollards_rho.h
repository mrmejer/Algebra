#ifndef PROJEKT_POLLARDS_RHO_H
#define PROJEKT_POLLARDS_RHO_H

#include "BigNum.h"
#include "BarretReducer.h"
#include "miller_rabin_test.h"

using namespace std;

/**
 * finds a non trivial factor of n
 * @param n the number to be factored
 * @param mt random number generator
 * @return a non trivial factor of n
 */
BigNum findFactor(BigNum& n, mt19937 &mt);

/**
 * finds a prime factorization of n
 * @param n a composite number to be factored
 * @return a vector of all prime factors of n
 * - multiples are repeated
 * - the primes are given in increasing order
 */
vector<BigNum> factor(BigNum n);

#endif