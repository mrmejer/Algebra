#include <iostream>
#include "lib/pollards_rho.h"

using namespace std;

int main()
{
    BigNum n;
    cin >> n;
    for(auto& f: factor(n)) cout<<f<<endl;

    return 0;
}