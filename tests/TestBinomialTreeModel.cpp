#include <gtest/gtest.h>
#include "../include/BinomialTreeModel.hpp"

TEST(BinomialTreeModelTest, AmericanOptionPricing) {
    BinomialTreeModel binomialTree(100, 0.03, 0.2);
    double price = binomialTree.priceAmericanOption(100.0, 105.0, 1.0, true); // Call option
    EXPECT_GT(price, 0.0);
}

TEST(BinomialTreeModelTest, EarlyExerciseCheck) {
    BinomialTreeModel binomialTree(100, 0.03, 0.2);
    double price = binomialTree.priceAmericanOption(100.0, 95.0, 1.0, false); // Put option
    EXPECT_GT(price, 0.0);
}

