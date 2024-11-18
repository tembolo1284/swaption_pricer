#include <gtest/gtest.h>
#include "../include/BlackModel.hpp"

TEST(BlackModelTest, SwaptionPricing) {
    double forwardRate = 0.025;
    double strikeRate = 0.03;
    double volatility = 0.2;
    double maturity = 1.0;
    double discountFactor = 0.98;

    double price = BlackModel::priceSwaption(forwardRate, strikeRate, volatility, maturity, discountFactor);
    EXPECT_GT(price, 0.0);
}

