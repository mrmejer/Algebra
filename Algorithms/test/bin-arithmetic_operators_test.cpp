#include <gtest/gtest.h>
#include "../lib/BigNum.h"

TEST(BinArithmetic, AndEquals) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_a.resize(10);
    big_a[9] = 1;
    big_a &= big_b;

    EXPECT_EQ(big_a, BigNum(a & b));
    EXPECT_EQ(big_b, BigNum(b));
}

TEST(BinArithmetic, And) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_a.resize(10);
    BigNum big_c = big_a & big_b;

    EXPECT_EQ(big_a, BigNum(a));
    EXPECT_EQ(big_b, BigNum(b));
    EXPECT_EQ(big_c, BigNum(a & b));
}

TEST(BinArithmetic, OrEquals) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_b.resize(10);
    big_a |= big_b;

    EXPECT_EQ(big_a, BigNum(a | b));
    EXPECT_EQ(big_b, BigNum(b));
}

TEST(BinArithmetic, Or) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_b.resize(10);
    BigNum big_c = big_a | big_b;

    EXPECT_EQ(big_a, BigNum(a));
    EXPECT_EQ(big_b, BigNum(b));
    EXPECT_EQ(big_c, BigNum(a | b));
}

TEST(BinArithmetic, XorEquals) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_b.resize(10);
    big_a.resize(8);
    big_a ^= big_b;

    EXPECT_EQ(big_a, BigNum(a ^ b));
    EXPECT_EQ(big_b, BigNum(b));
}

TEST(BinArithmetic, Xor) {
    unsigned long long a = 783625784937625384;
    unsigned long long b = 124374529045764856;
    BigNum big_a(a);
    BigNum big_b(b);
    big_b.resize(10);
    big_a.resize(8);
    BigNum big_c = big_a ^ big_b;

    EXPECT_EQ(big_a, BigNum(a));
    EXPECT_EQ(big_b, BigNum(b));
    EXPECT_EQ(big_c, BigNum(a ^ b));
}