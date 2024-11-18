#include <gtest/gtest.h>
#include "../include/MonteCarloPricer.hpp"

TEST(MonteCarloPricerTest, EuropeanOptionPricing) {
    MonteCarloPricer monteCarlo(10000, 100, 0.03, 0.2);
    auto payoffFunc = [](double finalPrice) { return std::max(0.0, finalPrice - 105.0); };
    double price = monteCarlo.priceEuropean(100.0, 1.0, payoffFunc);
    EXPECT_GT(price, 0.0);
}

TEST(MonteCarloPricerTest, AmericanOptionPricing) {
    MonteCarloPricer monteCarlo(10000, 100, 0.03, 0.2);
    auto payoffFunc = [](double finalPrice) { return std::max(0.0, finalPrice - 105.0); };
    double price = monteCarlo.priceAmerican(100.0, 1.0, payoffFunc);
    EXPECT_GT(price, 0.0);
}

