#include <iostream>

#include "gtest/gtest.h"
#include "bypass_tests/basic_tests/basic_check.hpp"

int main() {
    ::testing::InitGoogleTest();
    runbasictest();
    return RUN_ALL_TESTS();
}
