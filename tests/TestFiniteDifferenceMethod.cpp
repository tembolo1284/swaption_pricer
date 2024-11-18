#include <gtest/gtest.h>
#include "../include/FiniteDifferenceMethod.hpp"

TEST(FiniteDifferenceMethodTest, EuropeanOptionPricing) {
    FiniteDifferenceMethod fdm(100, 100, 0.03, 0.2);
    double price = fdm.priceEuropeanOption(100.0, 105.0, 1.0, FiniteDifferenceMethod::Call);
    EXPECT_GT(price, 0.0);
}

TEST(FiniteDifferenceMethodTest, AmericanOptionPricing) {
    FiniteDifferenceMethod fdm(100, 100, 0.03, 0.2);
    double price = fdm.priceAmericanOption(100.0, 105.0, 1.0, FiniteDifferenceMethod::Put);
    EXPECT_GT(price, 0.0);
}

