//
// Created by AK on 13/10/15.
//

#include "gtest/gtest.h"
#include "basic_check.hpp"
void runbasictest(){}

TEST(TestowyTest, test_eq) {
    EXPECT_EQ(1,0);
}

TEST(basic_check, test_neq) {
    EXPECT_NE(1, 0);
}
