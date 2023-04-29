#ifndef PROJEKT_BIGNUM_H
#define PROJEKT_BIGNUM_H

#include <string>
#include <iostream>

using namespace std;

class BarretReducer; // forward declaration

class BigNum
{
    unsigned* digits; // array of bits
    unsigned capacity; // capacity of the array
    mutable unsigned length; // length of the number in bits/32

public:

    BigNum();

    BigNum(unsigned long long value);

    BigNum(const BigNum& a);

    BigNum& operator = (unsigned long long value);

    BigNum& operator = (const BigNum& other);

    BigNum(const string& a);

    ~BigNum();

    /* General Functions and Operators */

    unsigned& operator [] (unsigned index) const;

    unsigned size() const;

    bool bit(unsigned index) const;

    void resize(unsigned newSize);

    void trim() const;

    unsigned bits() const;

    unsigned trailing_zeros() const;

    string binaryString() const;

    string decimalString() const;

    void dis() const;

    /* Logical Operators */

    bool operator == (unsigned long long a) const;

    bool operator == (const BigNum &a) const;

    bool operator != (const BigNum &a) const;

    bool operator ! () const;

    bool operator < (const BigNum &a) const;

    bool operator > (const BigNum &a) const;

    bool operator <= (const BigNum &a) const;

    bool operator >= (const BigNum &a) const;

    /* Arithmetic operators */

    BigNum operator ~ () const;

    void operator &= (const BigNum &a);

    BigNum operator & (const BigNum &a) const;

    void operator |= (const BigNum& a);

    BigNum operator | (const BigNum &a) const;

    void operator ^= (const BigNum &a);

    BigNum operator ^ (const BigNum &a) const;

    void operator >>= (unsigned a);

    BigNum operator >> (unsigned a) const;

    void operator <<= (unsigned a);

    BigNum operator << (unsigned a) const;

    void reverseBits();

    void operator += (const BigNum &a);

    BigNum operator + (const BigNum &a) const;

    void operator -= (const BigNum &a);

    BigNum operator - (const BigNum &a) const;

    void operator *= (unsigned a);

    BigNum operator * (unsigned a) const;

    BigNum operator * (const BigNum &a) const;

    void operator *= (const BigNum &a);

    /**
     * Calculates the integer part of 2^l/a
     * @param l the exponent
     * @return 2^l/a
     */
    BigNum inv(unsigned l) const;

    void operator %= (unsigned a);

    unsigned operator % (unsigned a) const;

    void operator %= (const BigNum& m);

    BigNum operator % (const BigNum& m) const;

    void operator /= (const BigNum& a);

    BigNum operator / (const BigNum& a) const;
};

ostream& operator<<(std::ostream& stream, BigNum const& a);

istream& operator>> (istream& is, BigNum& dt);

void read(BigNum* a);

BigNum gcd(BigNum a, BigNum b);

BigNum pow(BigNum a, BigNum b, BarretReducer& m);

BigNum pow(BigNum a, BigNum b, BigNum m);

#endif