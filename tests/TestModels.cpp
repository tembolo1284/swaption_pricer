#include <gtest/gtest.h>
#include "../include/HullWhiteModel.hpp"
#include "../include/ExtendedVasicekModel.hpp"
#include "../include/SABRModel.hpp"

TEST(HullWhiteModelTest, SwaptionPricing) {
    HullWhiteModel hwModel(0.03, 0.01);
    double price = hwModel.priceSwaption(0.025, 0.03, 1.0, 5.0);
    EXPECT_NE(price, 0.0);
}

TEST(ExtendedVasicekModelTest, SwaptionPricing) {
    ExtendedVasicekModel evModel(0.03, 0.01, 0.02);
    double price = evModel.priceSwaption(0.025, 0.03, 1.0, 5.0);
    EXPECT_NE(price, 0.0);
}

TEST(SABRModelTest, SwaptionPricing) {
    SABRModel sabrModel(0.2, 0.5, -0.2, 0.3);
    double price = sabrModel.priceSwaption(0.025, 0.03, 1.0);
    EXPECT_GT(price, 0.0);
}

