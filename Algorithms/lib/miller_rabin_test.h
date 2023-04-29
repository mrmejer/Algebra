#ifndef PROJEKT_MILLER_RABIN_TEST_H
#define PROJEKT_MILLER_RABIN_TEST_H

#include "BigNum.h"
#include "BarretReducer.h"

using namespace std;

bool checkComposite(unsigned a, BigNum n, BarretReducer& r);

bool isPrime(BigNum n);

#endif