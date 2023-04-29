#include <iostream>
#include "BigNum.h"
#include "BarretReducer.h"

using namespace std;

BigNum::BigNum() : BigNum(0) {}

BigNum::BigNum(unsigned long long value)
{
    digits = new unsigned[2];
    digits[0] = (unsigned)value;
    digits[1] = value >> 32;
    length = (value > UINT_MAX) ? 2 : 1;
    capacity = 2;
}

BigNum::BigNum(const BigNum& a)
{
    digits = new unsigned[a.capacity];
    memcpy(digits, a.digits, a.capacity * sizeof(unsigned));
    length = a.length;
    capacity = a.capacity;
}

BigNum& BigNum::operator = (unsigned long long value)
{
    resize(2);
    digits[0] = (unsigned)value;
    digits[1] = value >> 32;
    length = (value > UINT_MAX) ? 2 : 1;
    return *this;
}

BigNum& BigNum::operator = (const BigNum& other)
{
    if (this != &other) {
        length = other.length;
        capacity = other.capacity;
        delete[] digits;
        digits = new unsigned[capacity];
        memcpy(digits, other.digits, capacity * sizeof(unsigned ));
    }
    return *this;
}

BigNum::BigNum(const string& a) : BigNum(0)
{
    unsigned buffer = 0;
    for(int i = 0; i < a.length(); i++)
    {
        buffer = buffer * 10 + (a[i] - '0');
        if(i % 9 == 8)
        {
            *this *= 1000000000U;
            *this += buffer;
            buffer = 0;
        }
    }
    unsigned m = 1;
    for(int i = 0; i < a.length() % 9; i++) m *= 10;
    *this *= m;
    *this += buffer;
}

BigNum::~BigNum()
{
    delete [] digits;
}

/* General Functions and Operators */

unsigned& BigNum::operator [] (unsigned index) const { return digits[index]; }

unsigned BigNum::size() const { return length; }

bool BigNum::bit(unsigned index) const { return digits[index >> 5] & (1U << (index & 31)); }

void BigNum::resize(unsigned newSize)
{
    if(newSize > capacity)
    {
        while(newSize > capacity) capacity <<= 1;
        unsigned *newDigits = new unsigned[capacity];
        memcpy(newDigits, digits, length * sizeof(unsigned));
        delete [] digits;
        digits = newDigits;
    }
    if(newSize > length) memset(digits + length, 0, (newSize - length) << 2);
    length = newSize;
}

void BigNum::trim() const
{
    while(length > 1 && digits[length - 1] == 0) length--;
}

unsigned BigNum::bits() const
{
    trim();
    return (length << 5) - __builtin_clz(digits[length - 1]);
}

unsigned BigNum::trailing_zeros() const {
    trim();
    if(!*this) return 0;
    for(int i = 0; i < length; i++)
    {
        if(digits[i]) return (i << 5) + __builtin_ctz(digits[i]);
    }
}

string BigNum::binaryString() const
{
    string ret = string((length << 5) + length - 1, 0);
    int c = 0;
    for(int i = length - 1; i >= 0; i--)
    {
        for(int j = 31; j >= 0; j--)
        {
            ret[c++] = '0' + (bool)((digits[i]) & (1 << j));
        }
        if(i) ret[c++] = ' ';
    }
    return ret;
}

string BigNum::decimalString() const
{
    if(*this == 0) return "0";
    int decLen = 1;
    unsigned dec[length << 1];
    memset(dec, 0, length << 3);
    unsigned long long r;
    for(int i = length - 1; i >= 0; i--)
    {
        r = 0;
        for(int j = 0; j <= decLen; j++)
        {
            r = ((unsigned long long)dec[j] << 16) + r;
            dec[j] = r % 1000000000ULL;
            r /= 1000000000ULL;
        }
        if(dec[decLen]) decLen++;
        r = digits[i];
        for(int j = 0; j <= decLen; j++)
        {
            r = ((unsigned long long)dec[j] << 16) + r;
            dec[j] = r % 1000000000ULL;
            r /= 1000000000ULL;
        }
        if(dec[decLen]) decLen++;
    }

    string ret(decLen * 9, 0);
    int c = 0;
    for(int i = 0; i < decLen - 1; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            ret[c++] = '0' + (dec[i] % 10);
            dec[i] /= 10;
        }
    }
    while(dec[decLen - 1])
    {
        ret[c++] = '0' + (dec[decLen - 1] % 10);
        dec[decLen - 1] /= 10;
    }

    ret.resize(c);
    reverse(ret.begin(), ret.end());

    return ret;
}

void BigNum::dis() const{
    cout<<binaryString()<<endl;
}

/* Logical Operators */

bool BigNum::operator == (unsigned long long a) const
{
    return *this == BigNum(a);
}

bool BigNum::operator == (const BigNum &a) const
{
    trim();
    a.trim();
    if(length != a.length) return false;
    for(int i = 0; i < length; i++) if(digits[i] != a[i]) return false;
    return true;
}

bool BigNum::operator != (const BigNum &a) const { return !(*this == a); }

bool BigNum::operator ! () const
{
    trim();
    return length == 1 && digits[0] == 0;
}

bool BigNum::operator < (const BigNum &a) const
{
    trim();
    a.trim();
    if(length != a.length) return length < a.length;
    for(int i = length - 1; i >= 0; i--)
    {
        if(digits[i] > a[i]) return false;
        else if(digits[i] < a[i]) return true;
    }
    return false;
}

bool BigNum::operator > (const BigNum &a) const { return a < *this; }

bool BigNum::operator <= (const BigNum &a) const { return !(a < *this); }

bool BigNum::operator >= (const BigNum &a) const { return !(*this < a); }

/* Arithmetic operators */

BigNum BigNum::operator ~ () const
{
    BigNum ret;
    ret.resize(length);
    for(int i = 0; i < length; i++) ret[i] = ~digits[i];
    return ret;
}

void BigNum::operator &= (const BigNum &a)
{
    if(a.length < length) resize(a.length);
    for(int i = 0; i < a.length; i++) digits[i] &= a[i];
}

BigNum BigNum::operator & (const BigNum &a) const
{
    BigNum ret(*this);
    ret &= a;
    return ret;
}

void BigNum::operator |= (const BigNum& a)
{
    if(a.length > length) resize(a.length);
    for(int i = 0; i < a.length; i++) digits[i] |= a[i];
}

BigNum BigNum::operator | (const BigNum &a) const
{
    BigNum ret(*this);
    ret |= a;
    return ret;
}

void BigNum::operator ^= (const BigNum &a)
{
    if(a.length > length) resize(a.length);
    for(int i = 0; i < a.length; i++) digits[i] ^= a[i];
}

BigNum BigNum::operator ^ (const BigNum &a) const
{
    BigNum ret(*this);
    ret ^= a;
    return ret;
}

void BigNum::operator >>= (unsigned a)
{
    int b = a >> 5, s = a & 31;
    if(b >= length)
    {
        *this = 0;
        return;
    }

    if(s)
    {
        for(int i = 0; i < length - b - 1; i++) digits[i] = (digits[i + b] >> s) | (digits[i + b + 1] << (32 - s));
    }
    else
    {
        for(int i = 0; i < length - b - 1; i++) digits[i] = digits[i + b];
    }
    digits[length - b - 1] = digits[length - 1] >> s;
    resize(length - b);
}

BigNum BigNum::operator >> (unsigned a) const
{
    BigNum ret(*this);
    ret >>= a;
    return ret;
}

void BigNum::operator <<= (unsigned a)
{
    int b = a >> 5, s = a & 31;

    if(s)
    {
        resize(length + b + 1);
        digits[length - 1] = digits[length - b - 2] >> (32 - s);
        for(int i = length - 2; i > b; i--) digits[i] = digits[i] = (digits[i - b] << s) | (digits[i - b - 1] >> (32 -s));
        digits[b] = digits[0] << s;
    }
    else
    {
        resize(length + b);
        for(int i = length - 1; i >= b; i--) digits[i] = digits[i - b];
    }
    if(b) memset(digits, 0, b << 2);
}

BigNum BigNum::operator << (unsigned a) const
{
    BigNum ret(*this);
    ret <<= a;
    return ret;
}

void BigNum::reverseBits() {
    for(int i = 0; (i << 1) < length; i++) swap(digits[i], digits[length - i - 1]);
    for(int i = 0; i < length; i++)
    {
        unsigned n = digits[i];
        n = (n >> 1) & 0x55555555 | (n << 1) & 0xaaaaaaaa;
        n = (n >> 2) & 0x33333333 | (n << 2) & 0xcccccccc;
        n = (n >> 4) & 0x0f0f0f0f | (n << 4) & 0xf0f0f0f0;
        n = (n >> 8) & 0x00ff00ff | (n << 8) & 0xff00ff00;
        n = (n >> 16) & 0x0000ffff | (n << 16) & 0xffff0000;
        digits[i] = n;
    }
}

void BigNum::operator += (const BigNum &a)
{
    resize(max(length, a.length) + 1);
    unsigned carry = 0;
    for(int i = 0; i < a.length; i++)
    {
        unsigned old = digits[i];
        digits[i] += a[i] + carry;
        carry = carry ? digits[i] <= old : digits[i] < old;
    }
    for(int i = a.length; carry; i++)
    {
        digits[i]++;
        carry = !digits[i];
    }
    if(digits[length - 1] == 0) resize(length - 1);
}

BigNum BigNum::operator + (const BigNum &a) const
{
    BigNum ret(*this);
    ret += a;
    return ret;
}

void BigNum::operator -= (const BigNum &a)
{
    a.trim();
    unsigned carry = 0;
    for(int i = 0; i < a.length; i++)
    {
        unsigned old = digits[i];
        digits[i] -= a[i] + carry;
        carry = carry ? digits[i] >= old : digits[i] > old;
    }
    for(int i = a.length; carry; i++)
    {
        carry = !digits[i];
        digits[i]--;
    }
}

BigNum BigNum::operator - (const BigNum &a) const
{
    BigNum ret(*this);
    ret -= a;
    return ret;
}

void BigNum::operator *= (unsigned a)
{
    unsigned long long r = 0;
    for(int i = 0; i < length; i++)
    {
        r = (unsigned long long)digits[i] * a + (r >> 32);
        digits[i] = (unsigned)r;
    }
    if(r >> 32)
    {
        resize(length + 1);
        digits[length - 1] = r >> 32;
    }
}

BigNum BigNum::operator * (unsigned a) const
{
    BigNum ret(*this);
    ret *= a;
    return ret;
}

BigNum BigNum::operator * (const BigNum &a) const
{
    BigNum ret = 0;
    for(int i = 0; i < a.length; i++) if(a[i]) ret += ((*this * a[i]) << (i << 5));
    return ret;
}

void BigNum::operator *= (const BigNum &a)
{
    *this = *this * a;
}

/**
 * Calculates l most significant bits of 1/a
 * @param l the number of bits
 * @return 1/a
 */
BigNum BigNum::inv(unsigned l) const {
    trim();
    BigNum a = *this; // a: the number to be inverted

    if(a.bits() < max(l << 1, 32U)) a <<= max(l << 1, 32U) - a.bits(); // make sure that a has enough bits
    a.trim();

    unsigned first32 = (a >> (a.bits() - 32))[0];
    BigNum xn = (1ULL << 32) + ((unsigned long long)(-first32) << 32) / first32; // first approximation x0 = 2^64 / a

    int i = 32;
    while(i < l)
    {
        BigNum ac = a >> (a.bits() - (i << 1)); // ac: first 2i bits of a
        ac.trim();
        BigNum h = xn * ac;

        // correct xn if needed
        unsigned correction = 0;
        while(h[i >> 4] != ~0U)
        {
            h -= ac;
            correction++;
        }

        // get the further part of (xn * a)
        h >>= i;
        h.resize(i >> 5);

        // evaluate how much should be added to xn to correct the further bits
        h = ((~h + 1) * xn) >> i;


        // update xn
        xn = ((xn - correction) << i) + h + 1;
        xn.trim();

        i <<= 1;
    }
    xn >>= bits() + i - l; // adjust the number of bits

    // final corrections
    BigNum h = (xn * *this);
    while((h >> l) != 0ULL)
    {
        h -= *this;
        xn -= 1;
    }

    return xn;
}

void BigNum::operator %= (unsigned a)
{
    *this = *this % a;
}

unsigned BigNum::operator % (unsigned a) const
{
    unsigned long long res = 0;
    for(int i = length - 1; i >= 0; i--)
    {
        res = ((res << 32) + digits[i]) % a;
    }
    return res;
}

void BigNum::operator %= (const BigNum& m)
{
    if(*this < m) return;
    unsigned l = bits() + 1;
    BigNum q = (*this * m.inv(l)) >> l;
    *this -= q * m;
    if(*this >= m) *this -= m;
}

BigNum BigNum::operator % (const BigNum& m) const
{
    BigNum ret(*this);
    ret %= m;
    return ret;
}

void BigNum::operator /= (const BigNum& a)
{
    *this = *this / a;
}

BigNum BigNum::operator / (const BigNum& a) const
{
    unsigned l = bits() + 1;
    BigNum ret = (*this * a.inv(l)) >> l;
    if((ret + 1) * a <= *this) ret += 1;
    return ret;
}

ostream& operator<<(std::ostream& stream, BigNum const& a)
{
    return stream << a.decimalString();
}

istream& operator>> (istream& is, BigNum& dt)
{
    string s;
    is >> s;
    dt = BigNum(s);
    return is;
}

void read(BigNum* a)
{
    string s;
    cin >> s;
    *a = BigNum(s);
}

BigNum gcd(BigNum a, BigNum b)
{
    if(a == 0) return b;
    if(b == 0) return a;

    int tz = min(a.trailing_zeros(), b.trailing_zeros());
    a >>= a.trailing_zeros();
    b >>= b.trailing_zeros();

    while(true)
    {
        if(b > a) swap(a, b);

        if(b == 0) return a << tz;
        a -= b;
        a >>= a.trailing_zeros();
    }
}

BigNum pow(BigNum a, BigNum b, BarretReducer& m)
{
    a %= m.getModulo();
    BigNum ret = a;
    for(int i = b.bits() - 2; i >= 0; i--)
    {
        ret = m.mul(ret, ret);
        if(b.bit(i)) ret = m.mul(ret, a);
    }
    return ret;
}

BigNum pow(BigNum a, BigNum b, BigNum m)
{
    BarretReducer br(m);
    return pow(a, b, br);
}