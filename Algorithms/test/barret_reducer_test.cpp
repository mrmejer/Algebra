#include <gtest/gtest.h>
#include "../lib/BigNum.h"
#include "../lib/BarretReducer.h"

TEST(Reducer, small)
{
    BigNum a(382834074127352981);
    BigNum b(8352647122);

    BarretReducer br(b);

    br.reduce(a);

    EXPECT_EQ(a, 6955554939);
}