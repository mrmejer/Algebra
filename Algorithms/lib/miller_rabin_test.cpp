#include "miller_rabin_test.h"

using namespace std;

bool checkComposite(unsigned a, BigNum n, BarretReducer& r)
{
    n -= 1; // subtract 1 from n
    unsigned d = n.trailing_zeros(); // (n - 1) = 2^d * s
    BigNum x = pow(a, n >> d, r); // calculate a ^ s

    if(x == 1 || x == n) return false; // check a^s == 1 or a^s == n - 1
    for(int i = 1; i < d; i++)
    {
        x = r.mul(x, x);
        if(x == n) return false; // check a^( 2^i * s ) == n - 1
    }
    return true;
}

bool isPrime(BigNum n)
{
    if(n == 2) return true;
    if(n < 2 || !n.bit(0)) return false;

    BarretReducer r(n);
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    unsigned mx = -1;
    if(n.bits() <= 32) mx = n[0] - 1;
    uniform_int_distribution<unsigned> rnd(2, mx);

    for(int i = 0; i < 15; i++)
    {
        if(checkComposite(rnd(mt), n, r)) return false; // check for random base
    }
    return true;
}