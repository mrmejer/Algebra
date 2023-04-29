#include <iostream>
#include "lib/miller_rabin_test.h"

using namespace std;

int main()
{
    BigNum n;
    cin >> n;

    if(n < 2) cout<<"Input must be at least 2";
    else
    {
        if(isPrime(n)) cout<<"Prime";
        else cout<<"Composite";
    }

    return 0;
}