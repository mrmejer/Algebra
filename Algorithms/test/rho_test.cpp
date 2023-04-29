#include <gtest/gtest.h>
#include "../lib/pollards_rho.h"

TEST(Rho, square)
{
    vector<BigNum> exp = {1000000007, 1000000007};

    EXPECT_EQ(factor(BigNum("1000000014000000049")), exp);
}

TEST(Rho, prime)
{
    vector<BigNum> exp = {BigNum("806538382992834579864757001963")};

    EXPECT_EQ(factor(BigNum("806538382992834579864757001963")), exp);
}

TEST(Rho, factors10digits)
{
    vector<BigNum> exp = {BigNum("7714779419"), BigNum("8070895687")};

    EXPECT_EQ(factor(BigNum("62265179938963465853")), exp);
}

TEST(Rho, factors12digits)
{
    vector<BigNum> exp = {BigNum("609525683737"), BigNum("951157843543")};

    EXPECT_EQ(factor(BigNum("579755134927357545560191")), exp);
}

TEST(Rho, manyfactors)
{
    vector<BigNum> exp = {2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 7, 7, 11, 13, 13, 1000000009};

    EXPECT_EQ(factor(BigNum("172122640237103748192000")), exp);
}

TEST(Rho, first20primes)
{
    vector<BigNum> exp = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

    EXPECT_EQ(factor(BigNum("557940830126698960967415390")), exp);
}

/*TEST(Rho, bigNumber)
{
    vector<BigNum> exp = {2251498469081, 1907051542822289023};

    EXPECT_EQ(factor(BigNum("4293723629122942849328611197863")), exp);
}*/