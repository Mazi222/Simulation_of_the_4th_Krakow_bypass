#include <iostream>

#include "gtest/gtest.h"
#include "bypass_tests/basic_tests/basic_check.hpp"
#include "Simulation.hpp"

int main() {
    runbasictest();
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
