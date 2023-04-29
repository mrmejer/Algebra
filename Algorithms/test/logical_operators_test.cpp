#include <gtest/gtest.h>
#include "../lib/BigNum.h"

// Demonstrate some basic assertions.
TEST(Logical, Equals) {
    BigNum a(123);
    BigNum b(123);
    b.resize(10);

    EXPECT_TRUE(a == b);
}

TEST(Logical, EqualsLongLong) {
    BigNum a(2343534532434);
    long long b = 2343534532434;

    EXPECT_TRUE(a == b);
}