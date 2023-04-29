#include <iostream>
#include "lib/miller_rabin_test.h"

using namespace std;

int main()
{
    BigNum n;
    cin >> n;
    if(isPrime(n)) cout<<"Prime";
    else cout<<"Composite";
}