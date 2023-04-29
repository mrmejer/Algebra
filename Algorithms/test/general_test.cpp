#include <gtest/gtest.h>
#include "../lib/BigNum.h"

// Demonstrate some basic assertions.
TEST(General, AccessChunk)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    EXPECT_EQ(a[1], 4173853078);
}

TEST(General, Size)
{
    BigNum a(5234567890);

    EXPECT_EQ(a.size(), 2);
}

TEST(General, AccessBit)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    EXPECT_EQ(a.bit(39), 1);
}

TEST(General, Resize)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    a.resize(2);

    EXPECT_EQ(a.size(), 2);

    a.resize(10);

    EXPECT_EQ(a.size(), 10);
}

TEST(General, Trim)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    a.resize(10);
    a.trim();

    EXPECT_EQ(a.size(), 6);
}

TEST(General, Bits)
{
    BigNum a = 1;
    a <<= 453;
    a.resize(100);

    EXPECT_EQ(a.bits(), 454);
}

TEST(General, TrailingZeros)
{
    BigNum a(576473946442956800);

    EXPECT_EQ(a.trailing_zeros(), 42);
}

TEST(General, DecimalString)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    EXPECT_EQ(a.decimalString(), "12345678901234567890123456789012345678901234567890");
}

TEST(General, BinaryString)
{
    BigNum a("12345678901234567890123456789012345678901234567890");

    EXPECT_EQ(a.binaryString(), "00000000000000000000000000001000 01110010011111110110001101101001 10101010111110000011110010100001 01010000001001100111010001111010 11111000110001111111000110010110 11001110001111110000101011010010");
}