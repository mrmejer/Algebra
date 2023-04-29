#include "pollards_rho.h"

using namespace std;

BigNum findFactor(BigNum& n, mt19937 &mt)
{
    // check for small factors
    if(!n.bit(0)) return 2;
    unsigned t = n % 3234846615U;
    for(unsigned f: {3, 5, 7, 11, 13, 17, 19, 23, 29}) if((t % f) == 0) return f;
    t = n % 95041567U;
    for(unsigned f: {31, 37, 41, 43, 47}) if((t % f) == 0) return f;
    t = n % 4132280413;
    for(unsigned f: {53, 59, 61, 67, 71}) if((t % f) == 0) return f;

    // set initial state
    BarretReducer r(n);
    BigNum hare = BigNum(mt()) % n;
    BigNum tortoise;
    BigNum g;

    for(unsigned i = 1; true; i++)
    {
        if(!(i & (i - 1))) tortoise = hare;

        // move hare forward
        hare = hare * hare + 1;
        r.reduce(hare);

        if(hare > tortoise) g = gcd(n, hare - tortoise);
        else g = gcd(n, tortoise - hare);

        if(g == n) return findFactor(n, mt); // try again with different initial state
        if(g != 1) return g; // found a nontrivial factor of n
    }
}

vector<BigNum> factor(BigNum n)
{
    vector<BigNum> ret = {n};
    if(n < 2) return ret;
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

    for(int i = 0; i < ret.size(); i++)
    {
        while(!isPrime(ret[i]))
        {
            ret.push_back(findFactor(ret[i], mt));
            ret[i] /= ret.back();
        }
    }

    sort(ret.begin(), ret.end());
    return ret;
}