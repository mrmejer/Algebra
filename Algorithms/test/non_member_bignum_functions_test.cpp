#include <gtest/gtest.h>
#include "../lib/BigNum.h"

TEST(NonMember, GcdWith0)
{
    BigNum b("54672304273985634023753264203579624302522837430000000000");

    EXPECT_EQ(gcd(BigNum(0), b), b);
    EXPECT_EQ(gcd(b, BigNum(0)), b);
}

TEST(NonMember, Gcd)
{
    BigNum a("1000000000000000000000000000000000000000000000000000000000000");
    BigNum b("54672304273985634023753264203579624302522837430000000000");

    EXPECT_TRUE(gcd(a, b) == 10000000000ULL);
}

TEST(NonMember, Gcd2)
{
    BigNum a("34219607344412915306488018056439440");
    BigNum b("172122640237103748192000");

    EXPECT_TRUE(gcd(a, b) == 240ULL);
}



TEST(NonMember, Gcd3)
{
    BigNum a("438275923750273523407230523405235623052623");
    BigNum b("107212378026671993589341045803736448240");

    EXPECT_EQ(gcd(a, b), 19ULL);
}

TEST(NonMember, PowSmall)
{
    BigNum a("12");
    BigNum b("4");
    BigNum m("789");

    EXPECT_EQ(pow(a, b, m), BigNum("222"));
}

TEST(NonMember, Pow)
{
    BigNum a("382834074127352984444214234231");
    BigNum b("8352647122242375982344540047234");
    BigNum m("8455930283657644393734343648832");

    EXPECT_EQ(pow(a, b, m), BigNum("4127700522950619226865814057169"));
}