#include "BlackModel.hpp"
#include <cmath>

double BlackModel::priceSwaption(double forwardRate, double strikeRate, double volatility, double maturity, double discountFactor) {
    double d1 = (std::log(forwardRate / strikeRate) + 0.5 * volatility * volatility * maturity) / (volatility * std::sqrt(maturity));
    double d2 = d1 - volatility * std::sqrt(maturity);

    auto phi = [](double x) { return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0))); };

    double callPrice = discountFactor * (forwardRate * phi(d1) - strikeRate * phi(d2));
    return std::max(callPrice, 0.0);  // Return a non-negative price
}

double BlackModel::normalCDF(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

