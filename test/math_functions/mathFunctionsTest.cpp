
#include "mathFunctions.h"
#include "gtest/gtest.h"

namespace {

    TEST(SquareRootTest, BASIC) {
        EXPECT_EQ(5, mySqrt(25));
    }

}  // namespace
